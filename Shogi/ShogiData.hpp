#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_SHOGI_DATA
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_SHOGI_DATA
#include <cstddef>
#include <cstdint>
#include <array>
#include <limits>
#include <iostream>

namespace dtl {

	using shogi_point_t = std::int_fast32_t;
	using ShogiPoint = std::pair<shogi_point_t, shogi_point_t>;
	using shogi_t = std::uint_fast8_t;
	using ShogiBoard = std::array<std::array<shogi_t, 9>, 9>;

	enum :shogi_t {
		shogi_empty,
		shogi_empty2,
		shogi_empty3,
		shogi_empty4,

		shogi_next_place1,
		shogi_next_place2,
		shogi_next_all_place1,
		shogi_next_all_place2,
		
		//王将&玉将
		shogi_osho,
		shogi_1,
		shogi_gyokusho,
		shogi_2,
		
		//金将
		shogi_kinsho1,
		shogi_3,
		shogi_kinsho2,
		shogi_4,

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

	constexpr std::size_t shogi_hand_piece_num{ 40 };
	class ShogiHand
	{
	public:
		bool setPiece(const shogi_t piece_) noexcept {
			for (std::size_t i{}; i < shogi_hand_piece_num; ++i)
				if (piece[i] == 0) {
					piece[i] = piece_;
					return true;
				}
			return false;
		}
		bool searchPiece(const shogi_t piece_) noexcept {
			for (std::size_t i{}; i < shogi_hand_piece_num; ++i)
				if (piece[i] == piece_) return true;
			return false;
		}
		bool usePiece(const shogi_t piece_) noexcept {
			for (std::size_t i{}; i < shogi_hand_piece_num; ++i)
				if (piece[i] == piece_) {
					piece[i] = 0;
					return true;
				}
			return false;
		}
		shogi_t operator[](const std::size_t num_) noexcept {
			return piece[num_];
		}

	private:
		std::array<shogi_t, shogi_hand_piece_num> piece{ {} };
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
	constexpr dtl::ShogiBoard getCreateShogi() noexcept {
		dtl::ShogiBoard shogi_board{ {} };
		createShogi(shogi_board);
		return std::move(shogi_board);
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

	constexpr shogi_point_t fly_walk{ std::numeric_limits<shogi_point_t>::max() };

	
	constexpr std::size_t getPoint(const ShogiPoint& point_) noexcept {
		const shogi_point_t num_x{ (point_.first == 0) ? 1 : ((point_.first > 0) ? 2 : 0) };
		const shogi_point_t num_y{ (point_.second == 0) ? 1 : ((point_.second > 0) ? 2 : 0) };
		shogi_point_t num{ num_x + 3 * num_y };
		if (num >= 5) --num;
		return std::move(num);
	}

	template<typename Matrix_>
	constexpr auto getMatrixValue(const Matrix_& matrix_, const ShogiPoint& point_) noexcept {
		return matrix_[point_.second][point_.first];
	}

	template<typename Matrix_>
	bool isPutPiece(Matrix_& matrix_, const ShogiPoint& before_, const ShogiPoint& after_, const bool turn_) noexcept {
		const auto after_value{ getMatrixValue(matrix_,after_) };

		getPoint(after_);

		//0 1 2
		//3 ~ 4
		//5 6 7
	}

	constexpr std::array<ShogiPoint, 8> osho_walk{
		ShogiPoint(-1,-1),
		ShogiPoint(-1,0),
ShogiPoint(-1,1),
ShogiPoint(0,-1),
ShogiPoint(0,1),
ShogiPoint(1,-1),
ShogiPoint(1,0),
ShogiPoint(1,1)
	};

	constexpr std::array<ShogiPoint, 8> ryuma_walk{
ShogiPoint(-fly_walk,fly_walk),
ShogiPoint(fly_walk,fly_walk),
ShogiPoint(-fly_walk,-fly_walk),
ShogiPoint(fly_walk,-fly_walk),
ShogiPoint(0,1),
ShogiPoint(-1,0),
ShogiPoint(1,0),
ShogiPoint(0,-1)
	};

	constexpr std::array<ShogiPoint, 8> ryuo_walk{
ShogiPoint(0,fly_walk),
ShogiPoint(-fly_walk,0),
ShogiPoint(fly_walk,0),
ShogiPoint(0,-fly_walk),
ShogiPoint(-1,1),
ShogiPoint(1,1),
ShogiPoint(-1,-1),
ShogiPoint(1,-1)
	};

	constexpr std::array<ShogiPoint, 4> kakugyo_walk{
ShogiPoint(-fly_walk,fly_walk),
ShogiPoint(fly_walk,fly_walk),
ShogiPoint(-fly_walk,-fly_walk),
ShogiPoint(fly_walk,-fly_walk)
	};

	constexpr std::array<ShogiPoint, 4> hisha_walk{
ShogiPoint(0,fly_walk),
ShogiPoint(-fly_walk,0),
ShogiPoint(fly_walk,0),
ShogiPoint(0,-fly_walk)
	};

	constexpr std::array<ShogiPoint, 2> keima_walk{
ShogiPoint(-1,2),
ShogiPoint(1,2)
	};

	constexpr std::array<ShogiPoint, 1> kyosha_walk{
ShogiPoint(0,fly_walk)
	};
	constexpr std::array<ShogiPoint, 5> ginsho_walk{
ShogiPoint(0,1),
ShogiPoint(-1,1),
ShogiPoint(1,1),
ShogiPoint(-1,-1),
ShogiPoint(1,-1)
	};
	constexpr std::array<ShogiPoint, 6> kinsho_walk{
	ShogiPoint(0,1),
	ShogiPoint(-1,1),
	ShogiPoint(1,1),
	ShogiPoint(-1,0),
	ShogiPoint(1,0),
	ShogiPoint(0,-1)
	};
	constexpr std::array<ShogiPoint, 1> fuhyo_walk{
		ShogiPoint(0,1)
	};

}
#endif //Included Dungeon Template Library