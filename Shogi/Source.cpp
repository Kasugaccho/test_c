#include "Shogi.hpp"
#include <iostream>

void output(const dtl::turn_t turn_, const dtl::ShogiBoard& matrix_, const dtl::ShogiHands hands_) noexcept {
	std::cout << "------------------------------" << std::endl;
	dtl::outputTurn(turn_);
	std::cout << "/* 将棋盤 */" << std::endl;
	dtl::outputBoard(matrix_);
	std::cout << "/* 持ち駒 */" << std::endl;
	dtl::outputHands(hands_);
}

int main() {

	//盤を生成
	dtl::ShogiBoard matrix{ dtl::getCreateShogi() };
	//持ち駒
	dtl::ShogiHands hands{ {} };
	//ターン
	dtl::turn_t turn{};

	output(turn, matrix, hands);

	matrix[3][3] = dtl::shogi_gyokusho;
	dtl::nextTurn(turn);

	output(turn, matrix, hands);

	matrix[4][3] = dtl::shogi_gyokusho;
	dtl::nextTurn(turn);

	output(turn, matrix, hands);

	return 0;
}