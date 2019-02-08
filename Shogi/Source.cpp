#include "Shogi.hpp"
#include <array>
#include <iostream>

int main() {

	//盤を生成
	using dungeon_t = std::uint_fast8_t;
	std::array<std::array<dungeon_t, 9>, 9> matrix{ {} };

	//駒を置く
	dtl::createShogi(matrix);
	//表示
	dtl::output(matrix);
	
	return 0;
}