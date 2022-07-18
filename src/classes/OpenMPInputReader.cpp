//
// Created by rafael on 5/19/22.
//

#include <vector>
#include <iostream>
#include "../headers/OpenMPInputReader.h"

namespace cpyd {
    OpenMPInputReader::OpenMPInputReader(std::string &input)
            : InputReader(input) {}

    void OpenMPInputReader::readFile() {
        const unsigned int CANT_ROWS = 100000;
        // Buffer de 100,000 lineas del csv.
        std::vector<char> buffer(ROW_LEN * CANT_ROWS, 0);

        while (!m_InputFileStream.eof()) {
            m_InputFileStream.read(buffer.data(), (long) buffer.size());
            std::stringstream buffer_stream(buffer.data());

            std::vector<std::string> rows(CANT_ROWS, "");
            std::string aux;

            for (auto &row: rows) {
                std::getline(buffer_stream, row);
            }

#pragma omp parallel for default(none) shared(rows)
            for (auto &row: rows) {
                if (row.empty()) {
                    continue;
                }
                row = processRow(row);
            }

            std::stringstream s;
            for (auto &row: rows) {
                if (row.empty()) {
                    continue;
                }
                s << row << "\n";
            }

            m_auxOFStream << s.str();

            buffer = std::vector<char>(ROW_LEN * CANT_ROWS, 0);
        }
    }
} // cpyd