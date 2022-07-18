//
// Created by rafael on 5/17/22.
//

#include "../headers/SequentialInputReader.h"

namespace cpyd {
    SequentialInputReader::SequentialInputReader(std::string &input)
            : InputReader(input) {}

    void SequentialInputReader::readFile() {
        const unsigned int CANT_ROWS = 100000;
        std::vector<char> buffer(ROW_LEN * CANT_ROWS, 0);

        std::vector<cpyd::Resultado> res;

        while(!m_InputFileStream.eof()) {
            m_InputFileStream.read(buffer.data(), (long) buffer.size());
            std::stringstream buffer_stream(buffer.data());

            std::vector<std::string> rows(CANT_ROWS, "");
            std::string aux;

            for (auto &row: rows) {
                std::getline(buffer_stream, row);
            }

            std::stringstream s;
            for (auto &row: rows) {
                if (row.empty()) {
                    continue;
                }
                s << processRow(row)<< std::endl;
            }

            m_auxOFStream << s.str();
            buffer = std::vector<char>(ROW_LEN * CANT_ROWS, 0);
        }
    }
}
