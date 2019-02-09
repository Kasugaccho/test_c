#include "Shogi.hpp"

int main() {

	//盤を生成
	dtl::ShogiBoard matrix{ dtl::getCreateShogi() };

	//表示
	dtl::output(matrix);
	
	return 0;
}