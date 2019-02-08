#pragma once
#include <cstddef>

namespace dtl {

	enum :std::size_t {
		shogi_empty,
		shogi_next_place1,
		shogi_next_place2,
		//王将&玉将
		shogi_osho,
		shogi_gyokusho,
		//金将
		shogi_kinsho1,
		shogi_kinsho2,

		//ここより先は成る。----------------------------------------

		//飛車
		shogi_hisha1,
		shogi_ryuo1,
		shogi_hisha2,
		shogi_ryuo2,
		//角行
		shogi_kakugyo1,
		shogi_ryuma1,
		shogi_kakugyo2,
		shogi_ryuma2,

		//ここより先は成ると金と同じ動きになる。--------------------

		//銀将
		shogi_ginsho1,
		shogi_narigin1,
		shogi_ginsho2,
		shogi_narigin2,
		//桂馬
		shogi_keima1,
		shogi_narikei1,
		shogi_keima2,
		shogi_narikei2,
		//香車
		shogi_kyosha1,
		shogi_narikyo1,
		shogi_kyosha2,
		shogi_narikyo2,
		//歩兵
		shogi_fuhyo1,
		shogi_tokin1,
		shogi_fuhyo2,
		shogi_tokin2
	};

	template<typename Matrix_>
	constexpr void createShogi(Matrix_& matrix_) noexcept {
		if (matrix_.size() < 9 || matrix_[0].size() < 9) return;
		//0行目
		matrix_[0][0] = matrix_[0][matrix_[0].size() - 1] = shogi_kyosha1;
		matrix_[0][1] = matrix_[0][matrix_[0].size() - 2] = shogi_keima1;
		matrix_[0][2] = matrix_[0][matrix_[0].size() - 3] = shogi_ginsho1;
		matrix_[0][3] = matrix_[0][matrix_[0].size() - 4] = shogi_kinsho1;
		matrix_[0][4] = shogi_osho;
		//1行目
		matrix_[1][1] = shogi_hisha1;
		matrix_[1][matrix_[1].size() - 2] = shogi_kakugyo1;
		//2行目
		for (std::size_t col{}; col < matrix_[2].size(); ++col)
			matrix_[2][col] = shogi_fuhyo1;
		//last-2行目
		for (std::size_t col{}; col < matrix_[matrix_.size() - 3].size(); ++col)
			matrix_[matrix_.size() - 3][col] = shogi_fuhyo2;
		//last-1行目
		matrix_[matrix_.size() - 1][0] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 1] = shogi_kyosha2;
		matrix_[matrix_.size() - 1][1] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 2] = shogi_keima2;
		matrix_[matrix_.size() - 1][2] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 3] = shogi_ginsho2;
		matrix_[matrix_.size() - 1][3] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 4] = shogi_kinsho2;
		matrix_[matrix_.size() - 1][4] = shogi_gyokusho;
		//last行目
		matrix_[matrix_.size() - 2][1] = shogi_kakugyo2;
		matrix_[matrix_.size() - 2][matrix_[matrix_.size() - 2].size() - 2] = shogi_hisha2;


	}

	template<typename Matrix_Int_>
	constexpr bool isEmpty(const Matrix_Int_ koma_) noexcept {
		return koma_ == static_cast<Matrix_Int_>(dtl::shogi_empty);
	}
	template<typename Matrix_Int_>
	constexpr bool isOsho(const Matrix_Int_ koma_) noexcept {
		return koma_ == static_cast<Matrix_Int_>(dtl::shogi_osho);
	}
	template<typename Matrix_Int_>
	constexpr bool isGyokusho(const Matrix_Int_ koma_) noexcept {
		return koma_ == static_cast<Matrix_Int_>(dtl::shogi_gyokusho);
	}


	template<typename Matrix_Int_>
	constexpr bool isNarikin(const Matrix_Int_ koma_) noexcept {
		if (koma_ >= shogi_ginsho1 && shogi_narigin1 % 2 == koma_ % 2) return true;
		return false;
	}
	template<typename Matrix_Int_>
	constexpr bool isNari(const Matrix_Int_ koma_) noexcept {
		if (koma_ >= shogi_hisha1 && shogi_ryuo1 % 2 == koma_ % 2) return true;
		return false;
	}
	template<typename Matrix_Int_>
	constexpr void setNari(Matrix_Int_& koma_) noexcept {
		if (!isNari(koma_)) return false;
		++koma_;
		return true;
	}

	template<typename Matrix_Int_>
	constexpr void outputSw(const Matrix_Int_ koma_) noexcept {
		switch (koma_)
		{
			case shogi_empty:std::cout<<"・　";break;
				case shogi_next_place1:std::cout<<"　　";break;
				case shogi_next_place2:std::cout<<"　　";break;
				//王将&玉将
				case shogi_osho:std::cout<<"王↓";break;
				case shogi_gyokusho:std::cout<<"玉↑";break;
				//金将
				case shogi_kinsho1:std::cout<<"金↓";break;
				case shogi_kinsho2:std::cout<<"金↑";break;

				//ここより先は成る。----------------------------------------

				//飛車
				case shogi_hisha1:std::cout<<"飛↓";break;
				case shogi_ryuo1:std::cout<<"龍↓";break;
				case shogi_hisha2:std::cout<<"飛↑";break;
				case shogi_ryuo2:std::cout<<"龍↑";break;
				//角行
				case shogi_kakugyo1:std::cout<<"角↓";break;
				case shogi_ryuma1:std::cout<<"馬↓";break;
				case shogi_kakugyo2:std::cout<<"角↑";break;
				case shogi_ryuma2:std::cout<<"馬↑";break;

				//ここより先は成ると金と同じ動きになる。--------------------

				//銀将
				case shogi_ginsho1:std::cout<<"銀↓";break;
				case shogi_narigin1:std::cout<<"成↓";break;
				case shogi_ginsho2:std::cout<<"銀↑";break;
				case shogi_narigin2:std::cout<<"成↑";break;
				//桂馬
				case shogi_keima1:std::cout<<"桂↓";break;
				case shogi_narikei1:std::cout<<"成↓";break;
				case shogi_keima2:std::cout<<"桂↑";break;
				case shogi_narikei2:std::cout<<"成↑";break;
				//香車
				case shogi_kyosha1:std::cout<<"香↓";break;
				case shogi_narikyo1:std::cout<<"成↓";break;
				case shogi_kyosha2:std::cout<<"香↑";break;
				case shogi_narikyo2:std::cout<<"成↑";break;
				//歩兵
				case shogi_fuhyo1:std::cout<<"歩↓";break;
				case shogi_tokin1:std::cout<<"と↓";break;
				case shogi_fuhyo2:std::cout<<"歩↑";break;
				case shogi_tokin2:std::cout << "と↑"; break;
		}
	}

	template<typename Matrix_>
	constexpr void output(Matrix_& matrix_) noexcept {
		for (std::size_t row{}; row < matrix_.size(); ++row) {
			for (std::size_t col{}; col < matrix_[row].size(); ++col)
				outputSw(matrix_[row][col]);
			std::cout << std::endl;
		}
	}

}