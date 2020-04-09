#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

static constexpr unsigned int YEAR_CHARACTERS = 4;
static constexpr unsigned int ROW_YEAR = 0;
static constexpr unsigned int ROW_PRODUCT = 1;
static constexpr unsigned int ROW_COMPANY = 7;

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "usage : application <input_file_location> <output_file_location>" << argc << std::endl;
        return -1;
    }

    // read the input file
    std::ifstream input_file;
    input_file.open(argv[1], std::ios::in);

    if (!input_file.is_open()) {
        std::cout << "Invalid input file" << std::endl;
        return -1;
    }

    std::ofstream output_file;
    output_file.open(argv[2], std::ios::out | std::ofstream::trunc);
    if (!output_file.is_open()) {
        std::cout << "Invalid output file" << std::endl;
        return -1;
    }

    // temp string for saving a line when reading from file
    std::string line;

    std::unordered_map <std::string, std::unordered_map<std::string, unsigned int>> report_data_exp;

    // csv data each row is a vector of strings. each string is for one field
    std::vector <std::vector<std::string>> csv_data;

    // find total number of columns 
    // more hacks! logic is shit!
    getline(input_file, line);
    unsigned int columns = 1;
    for (unsigned int i = 0; i < line.size(); i++) {
        if (line[i] == ',')
            columns++;
    }

    unsigned int csv_row_index = 0;
    char current_character = 0;

    while (!input_file.eof()) {
        std::vector <std::string> row_data(columns, std::string());
        csv_row_index++;
        unsigned int column_index = 0;
        bool inside_quatation = false;

        // get a row of data lots of hacks
        // not the fastest solution or the best looking
        while (column_index < columns) {
            // should be only for company name
            current_character = std::tolower(input_file.get());

            if (input_file.eof())
                break;

            if (column_index == columns - 1) {
                if (current_character == '\n') {
                    break;
                }
            }

            row_data[column_index].push_back(current_character);

            if (inside_quatation) {
                if (current_character == '"') {
                    inside_quatation = false;
                    continue;
                }
            } else if (!inside_quatation) {
                if (current_character == ',') {
                    column_index++;
                }

                if (current_character == '"') {
                    inside_quatation = true;
                    continue;
                }
            }
        }
        // create a mapping using the f(year, complaint) as unique key for the first mapping
        // second mapping is for complaints per company in that specific complaint
        if (row_data[ROW_YEAR] != "") {
            report_data_exp
            [row_data[ROW_PRODUCT]+ "," +std::string(row_data[ROW_YEAR], 0, YEAR_CHARACTERS)]
            [row_data[ROW_COMPANY]]++;
        }
        //csv_data.push_back(row_data);
    }

    output_file << "Complaint,Date,total,companies,highest company percentage\n";

    // You can remove std::cout so the app doesnt print the data to console
    // for( const auto& n : u ) 
    for (auto iterator : report_data_exp) {
        unsigned int total = 0, max_per_company = 0;
        std::cout << iterator.first << " ---- ";
        output_file << iterator.first << ",";
        for (auto sub_iterator : iterator.second) {
            total += sub_iterator.second;
            max_per_company = std::max(max_per_company, sub_iterator.second);
        }
        std::cout << "total: " << total
                  << " - number of companies: " << iterator.second.size()
                  << " max percentage: " << std::round((float) max_per_company / total * 100.0f)
                  << "\n\n";

        output_file << total << ","
                    << iterator.second.size() << ","
                    << std::round((float) max_per_company / total * 100.0f)
                    << '\n';
    }
    input_file.close();
    output_file.close();
}
