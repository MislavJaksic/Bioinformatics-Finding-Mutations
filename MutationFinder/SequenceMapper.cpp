#include "SequenceMapper.h"

std::map<char, char> SequenceMapper::reverse_nucleobase = {{'0', '3'}, {'1', '2'}, {'2', '1'}, {'3', '0'}};
int SequenceMapper::indel = 5;
int SequenceMapper::missmatch_1 = 1;
int SequenceMapper::missmatch_2 = 5;

static std::map<std::tuple<char, char>, int> initPam() {
    std::map<std::tuple<char, char>, int> pam_matrix = {};
    for (char c1 = '0'; c1<= '3'; c1++) {
        for (char c2 = '0'; c2<= '3'; c2++) {
            std::tuple<char, char> pamTouple = std::make_tuple(c1, c2);
            if (c1 == c2) {
                pam_matrix.insert( std::pair<std::tuple<char, char>,int>(pamTouple, 0) );
            } else if (abs(c1 - c2) == 2) {
                pam_matrix.insert( std::pair<std::tuple<char, char>,int>(pamTouple, SequenceMapper::missmatch_1) );
            } else {
                pam_matrix.insert( std::pair<std::tuple<char, char>,int>(pamTouple, SequenceMapper::missmatch_2) );
            }
        }
    }
    return pam_matrix;
}

std::map<std::tuple<char, char>, int> SequenceMapper::pam = initPam();

std::vector<unsigned int> SequenceMapper::getMatchingPositions(Sequence &sequence_A, Sequence &sequence_B) {
  std::vector<unsigned int> positions{};

  for (const KmerTriple& kmer_triple : sequence_B.getMinimizers()) {
        int k = kmer_triple.GetKey().getKmer().Length();
        //bool is_on_reverse_helix = kmer_triple.GetKey().isOnReverseHelix();
        unsigned int position_B = kmer_triple.GetPosition();
        //std::map<char, char> reverse_nucleobase = {{'0', '3'}, {'1', '2'}, {'2', '1'}, {'3', '0'}};

        KmerKey key_true{kmer_triple.GetKey().getKmer(), false};
        KmerKey key_reverse{kmer_triple.GetKey().getKmer(), true};
        std::vector<unsigned int> positions_true = sequence_A.minimizer_index[key_true];
        std::vector<unsigned int> positions_reverse = sequence_A.minimizer_index[key_reverse];
        bool is_found_true = positions_true.size() >= 1;
        bool is_found_reverse = positions_reverse.size() >= 1;

        if (is_found_true) {
            for (auto& position_A : positions_true) {
                int true_position = position_A;
                 for (int i=1; i<=5; i++) {
                    int pos_A_check = position_A - i;
                    int pos_B_check = position_B - i;
                    if (pos_A_check < 0 || pos_B_check < 0)
                        continue;

                    if (sequence_A.getSequence()[pos_A_check] != sequence_B.getSequence()[pos_B_check]) {
                        true_position = -1;
                        break;
                    }

                    pos_A_check = position_A + k + i;
                    pos_B_check = position_B + k + i;
                    if (pos_A_check >= (int)sequence_A.getSequence().Length() || pos_B_check >= (int)sequence_B.getSequence().Length())
                        continue;

                    if (sequence_A.getSequence()[pos_A_check] != sequence_B.getSequence()[pos_B_check]) {
                        true_position = -1;
                        break;
                    }
                 }

                 if (true_position > -1) {
                    positions.push_back(position_A);
                    positions.push_back(position_B);
                    positions.push_back(0);
                    positions.push_back(k);
                    return positions;
                 }
            }
        }
        if (is_found_reverse) {
            for (auto& position_A : positions_true) {
                int true_position = position_A;
                 for (int i=1; i<=5; i++) {
                    int pos_A_check = position_A - i;
                    int pos_B_check = position_B - i;
                    if (pos_A_check < 0 || pos_B_check < 0)
                        continue;

                    if (reverse_nucleobase[sequence_A.getSequence()[pos_A_check]] != sequence_B.getSequence()[pos_B_check]) {
                        true_position = -1;
                        break;
                    }

                    pos_A_check = position_A + k + i;
                    pos_B_check = position_B + k + i;
                    if (pos_A_check >= (int)sequence_A.getSequence().Length() || pos_B_check >= (int)sequence_B.getSequence().Length())
                        continue;

                    if (reverse_nucleobase[sequence_A.getSequence()[pos_A_check]] != sequence_B.getSequence()[pos_B_check]) {
                        true_position = -1;
                        break;
                    }
                 }

                 if (true_position > -1) {
                    positions.push_back(position_A);
                    positions.push_back(position_B);
                    positions.push_back(1);
                    positions.push_back(k);
                    return positions;
                 }
            }
        }
    }



  return positions;
}

std::vector<mutation> SequenceMapper::getGlobalMutations(Sequence &sequence_A, Sequence &sequence_B, int position_A, int N, int position_B, int M) {
    std::vector<mutation> mutations{};
    int kN = M/100;

    std::map<std::tuple<int, int>, cell> m;

    cell c_init{};
    std::tuple<int, int> m_position_init = std::make_tuple(0, 0);
    m.insert( std::pair<std::tuple<int, int>, cell>(m_position_init, c_init) );

    for (int i = 1; i<= kN; i++) {
        std::tuple<int, int> m_position_1 = std::make_tuple(0, i);
        std::tuple<int, int> m_position_2 = std::make_tuple(i, 0);

        cell c1{};
        c1.cost = i * SequenceMapper::indel;
        c1.parrent = &(m[std::make_tuple(0, i-1)]);

        cell c2{};
        c2.cost = i * SequenceMapper::indel;
        c2.parrent = &(m[std::make_tuple(i-1, 0)]);

        m.insert( std::pair<std::tuple<int, int>, cell>(m_position_1, c1) );
        m.insert( std::pair<std::tuple<int, int>, cell>(m_position_2, c2) );
    }

    return mutations;
}

std::vector<mutation> SequenceMapper::getMutations(Sequence &sequence_A, Sequence &sequence_B) {
    std::vector<mutation> mutations{};

    std::vector<unsigned int> positions = this->getMatchingPositions(sequence_A, sequence_B);

    int k = positions[3];
    bool reverse = (positions[2] == 1);
    int position_A = positions[0];
    int position_B = positions[1];


    return mutations;
}
