#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_SHOGI_OUTPUT
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_SHOGI_OUTPUT
#include "ShogiData.hpp"
#include <cstddef>
#include <cstdint>

//Dungeon Template Library Namespace
namespace dtl {

	template<typename Matrix_Int_>
	constexpr void outputSw(const Matrix_Int_ koma_) noexcept {
		switch (koma_)
		{
		case shogi_empty:std::cout << "・　"; break;
		case shogi_next_place2:std::cout << "　　"; break;
		case shogi_next_place1:std::cout << "　　"; break;
			//王将&玉将
		case shogi_osho:std::cout << "王↓"; break;
		case shogi_gyokusho:std::cout << "玉↑"; break;
			//金将
		case shogi_kinsho2:std::cout << "金↓"; break;
		case shogi_kinsho1:std::cout << "金↑"; break;

			//ここより先は成る。----------------------------------------

			//飛車
		case shogi_hisha2:std::cout << "飛↓"; break;
		case shogi_ryuo2:std::cout << "龍↓"; break;
		case shogi_hisha1:std::cout << "飛↑"; break;
		case shogi_ryuo1:std::cout << "龍↑"; break;
			//角行
		case shogi_kakugyo2:std::cout << "角↓"; break;
		case shogi_ryuma2:std::cout << "馬↓"; break;
		case shogi_kakugyo1:std::cout << "角↑"; break;
		case shogi_ryuma1:std::cout << "馬↑"; break;

			//ここより先は成ると金と同じ動きになる。--------------------

			//銀将
		case shogi_ginsho2:std::cout << "銀↓"; break;
		case shogi_narigin2:std::cout << "成↓"; break;
		case shogi_ginsho1:std::cout << "銀↑"; break;
		case shogi_narigin1:std::cout << "成↑"; break;
			//桂馬
		case shogi_keima2:std::cout << "桂↓"; break;
		case shogi_narikei2:std::cout << "成↓"; break;
		case shogi_keima1:std::cout << "桂↑"; break;
		case shogi_narikei1:std::cout << "成↑"; break;
			//香車
		case shogi_kyosha2:std::cout << "香↓"; break;
		case shogi_narikyo2:std::cout << "成↓"; break;
		case shogi_kyosha1:std::cout << "香↑"; break;
		case shogi_narikyo1:std::cout << "成↑"; break;
			//歩兵
		case shogi_fuhyo2:std::cout << "歩↓"; break;
		case shogi_tokin2:std::cout << "と↓"; break;
		case shogi_fuhyo1:std::cout << "歩↑"; break;
		case shogi_tokin1:std::cout << "と↑"; break;
		}
		//if (isMyPiece(koma_, dtl::sente_id))std::cout << "(先手)";
		//else if (isMyPiece(koma_, dtl::gote_id))std::cout << "(後手)";
	}

	template<typename Matrix_>
	constexpr void outputBoard(const Matrix_& matrix_) noexcept {
		for (std::size_t row{}; row < matrix_.size(); ++row) {
			for (std::size_t col{}; col < matrix_[row].size(); ++col)
				outputSw(matrix_[row][col]);
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	void outputHands(const dtl::ShogiHands& shogi_hands_) noexcept {
		std::cout << "先手:";
		for (std::size_t i{}; i < shogi_hands_[sente_id].size(); ++i)
			outputSw(shogi_hands_[sente_id][i]);
		std::cout << std::endl;
		std::cout << "後手:";
		for (std::size_t i{}; i < shogi_hands_[gote_id].size(); ++i)
			outputSw(shogi_hands_[gote_id][i]);
		std::cout << std::endl;
		std::cout << std::endl;
	}
	void outputTurn(const turn_t turn_) noexcept {
		std::cout << "[";
		switch (turn_)
		{
		case sente_id:std::cout << "先手"; break;
		case gote_id:std::cout << "後手"; break;
		}
		std::cout << "]" << std::endl;
	}


}

#endif //Included Dungeon Template Library