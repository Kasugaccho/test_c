#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_SHOGI_DATA
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_SHOGI_DATA
#include <cstddef>
#include <cstdint>
#include <array>
#include <limits>
#include <iostream>

namespace dtl {

	//駒の座標指定の型
	using shogi_point_t = std::int_fast32_t;
	//駒の座標を示す型
	using ShogiPoint = std::pair<shogi_point_t, shogi_point_t>;
	//駒の型
	using shogi_t = std::uint_fast8_t;
	//将棋盤の型
	using ShogiBoard = std::array<std::array<shogi_t, 9>, 9>;

	using turn_t = std::uint_fast8_t;

	using ShogiPieceMove = std::array<ShogiPoint, 8>;

	constexpr std::size_t sente{ 0 };
	constexpr std::size_t gote{ 1 };

	enum :turn_t {
		sente_id,
		gote_id,
	};

	//駒の種類
	enum :shogi_t {
		//空
		shogi_empty,
		shogi_empty2,
		shogi_empty3,
		shogi_empty4,

		//ツール
		shogi_next_place1,
		shogi_next_place2,
		shogi_next_all_place1,
		shogi_next_all_place2,
		
		//王将&玉将
		shogi_gyokusho,
		shogi_1,
		shogi_osho,
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

	//駒であるか調べる
	constexpr bool isPiece(const shogi_t piece_) noexcept {
		return piece_ >= shogi_gyokusho;
	}

	//持ち駒
	constexpr std::size_t shogi_hand_piece_num{ 40 };
	class ShogiHand
	{
	public:
		//持ち駒をセットする
		bool setPiece(const shogi_t piece_) noexcept {
			if (!dtl::isPiece(piece_)) return false;
			for (std::size_t i{}; i < shogi_hand_piece_num; ++i)
				if (piece[i] == 0) {
					piece[i] = piece_;
					return true;
				}
			return false;
		}
		//指定した駒があるか調べる
		bool searchPiece(const shogi_t piece_) const noexcept {
			for (std::size_t i{}; i < shogi_hand_piece_num; ++i)
				if (piece[i] == piece_) return true;
			return false;
		}
		//指定した駒があるか調べて、あったら使う
		bool usePiece(const shogi_t piece_) noexcept {
			for (std::size_t i{}; i < shogi_hand_piece_num; ++i)
				if (piece[i] == piece_) {
					piece[i] = 0;
					return true;
				}
			return false;
		}
		shogi_t operator[](const std::size_t num_) const noexcept {
			return piece[num_];
		}
		constexpr size_t size() const noexcept {
			return shogi_hand_piece_num;
		}

	private:
		std::array<shogi_t, shogi_hand_piece_num> piece{ {} };
	};
	using ShogiHands = std::array<ShogiHand, 2>;



	//将棋盤の駒の位置を初期化する
	template<typename Matrix_>
	constexpr void createShogi(Matrix_& matrix_) noexcept {
		if (matrix_.size() < 9 || matrix_[0].size() < 9) return;
		//0行目
		matrix_[0][0] = matrix_[0][matrix_[0].size() - 1] = shogi_kyosha2;
		matrix_[0][1] = matrix_[0][matrix_[0].size() - 2] = shogi_keima2;
		matrix_[0][2] = matrix_[0][matrix_[0].size() - 3] = shogi_ginsho2;
		matrix_[0][3] = matrix_[0][matrix_[0].size() - 4] = shogi_kinsho2;
		matrix_[0][4] = shogi_osho;
		//1行目
		matrix_[1][1] = shogi_hisha2;
		matrix_[1][matrix_[1].size() - 2] = shogi_kakugyo2;
		//2行目
		for (std::size_t col{}; col < matrix_[2].size(); ++col)
			matrix_[2][col] = shogi_fuhyo2;
		//last-2行目
		for (std::size_t col{}; col < matrix_[matrix_.size() - 3].size(); ++col)
			matrix_[matrix_.size() - 3][col] = shogi_fuhyo1;
		//last-1行目
		matrix_[matrix_.size() - 1][0] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 1] = shogi_kyosha1;
		matrix_[matrix_.size() - 1][1] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 2] = shogi_keima1;
		matrix_[matrix_.size() - 1][2] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 3] = shogi_ginsho1;
		matrix_[matrix_.size() - 1][3] = matrix_[matrix_.size() - 1][matrix_[matrix_.size() - 1].size() - 4] = shogi_kinsho1;
		matrix_[matrix_.size() - 1][4] = shogi_gyokusho;
		//last行目
		matrix_[matrix_.size() - 2][1] = shogi_kakugyo1;
		matrix_[matrix_.size() - 2][matrix_[matrix_.size() - 2].size() - 2] = shogi_hisha1;


	}
	//初期の駒の配置を返す
	constexpr dtl::ShogiBoard getCreateShogi() noexcept {
		dtl::ShogiBoard shogi_board{ {} };
		createShogi(shogi_board);
		return std::move(shogi_board);
	}


	//成金になれるかチェック
	constexpr bool isNarikin(const shogi_t piece_) noexcept {
		if (piece_ >= shogi_ginsho1 && shogi_narigin1 % 2 == piece_ % 2) return true;
		return false;
	}
	//成るかチェック
	constexpr bool isNari(const shogi_t piece_) noexcept {
		if (piece_ >= shogi_hisha1 && shogi_ryuo1 % 2 == piece_ % 2) return true;
		return false;
	}
	//成る
	constexpr bool setNari(shogi_t& piece_) noexcept {
		if (!isNari(piece_)) return false;
		++piece_;
		return true;
	}
	//空かチェック
	constexpr bool isEmpty(const dtl::shogi_t piece_) noexcept {
		return piece_ < dtl::shogi_gyokusho;
	}
	constexpr bool isOsho(const dtl::shogi_t piece_) noexcept {
		return piece_ == dtl::shogi_osho;
	}
	constexpr bool isGyokusho(const dtl::shogi_t piece_) noexcept {
		return piece_ == dtl::shogi_gyokusho;
	}

	//指定した座標の値を返す
	template<typename Matrix_>
	constexpr auto getMatrixValue(const Matrix_& matrix_, const ShogiPoint& point_) noexcept {
		return matrix_[point_.second][point_.first];
	}
	template<typename Matrix_>
	constexpr void setMatrixValue(Matrix_& matrix_, const ShogiPoint& point_, const shogi_t piece_) noexcept {
		matrix_[point_.second][point_.first] = piece_;
	}

	constexpr bool isSenteMod(const dtl::shogi_t piece_) noexcept {
		return (piece_ == 0 || piece_ == 1) ? true : false;
	}
	constexpr bool isGoteMod(const dtl::shogi_t piece_) noexcept {
		return (piece_ == 2 || piece_ == 3) ? true : false;
	}
	//そのターンの者の駒であるか調べる
	constexpr bool isMyPiece(const dtl::shogi_t piece_, const turn_t turn_) noexcept {
		return (isPiece(piece_)) ? ((turn_ == dtl::sente_id) ? isSenteMod(piece_ & 3) : ((turn_ == dtl::gote_id) ? isGoteMod(piece_ & 3) : false)) : false;
	}
	//そのターンの者の駒であるか調べる
	template<typename Matrix_>
	constexpr bool isMyPiece(const Matrix_& matrix_, const ShogiPoint& point_, const turn_t turn_) noexcept {
		return isMyPiece(getMatrixValue(matrix_, point_), turn_);
	}



	bool nextTurn(turn_t& turn_) noexcept {
		if (turn_ > gote_id) return false;
		if (turn_) turn_ = sente_id;
		else turn_ = gote_id;
		return true;
	}

	constexpr shogi_point_t fly_walk{ std::numeric_limits<shogi_point_t>::max() };

	//移動点を取得
	constexpr std::size_t getPoint(const ShogiPoint& point_) noexcept {
		const shogi_point_t num_x{ (point_.first == 0) ? 1 : ((point_.first > 0) ? 2 : 0) };
		const shogi_point_t num_y{ (point_.second == 0) ? 1 : ((point_.second > 0) ? 2 : 0) };
		shogi_point_t num{ num_x + 3 * num_y };
		if (num >= 5) --num;
		return std::move(num);
	}

	//駒を置く
	template<typename Matrix_>
	bool isPutPiece(Matrix_& matrix_, const ShogiPoint& before_, const ShogiPoint& after_, const turn_t turn_) noexcept {
		const auto before_value{ getMatrixValue(matrix_,before_) };
		const auto after_value{ getMatrixValue(matrix_,after_) };

		if (!dtl::isMyPiece(before_value, turn_)) return false;

		getPoint(after_);

		//0 1 2
		//3 ~ 4
		//5 6 7
		//セット
		setMatrixValue(matrix_, before_, dtl::shogi_empty);
		setMatrixValue(matrix_, after_, before_value);
		return true;
	}

	constexpr ShogiPieceMove osho_walk{
		ShogiPoint(-1,-1),
		ShogiPoint(0,-1),
		ShogiPoint(1,-1),

		ShogiPoint(-1,0),
		ShogiPoint(1,0),

		ShogiPoint(-1,1),
		ShogiPoint(0,1),
		ShogiPoint(1,1)
	};

	constexpr ShogiPieceMove ryuma_walk{
		ShogiPoint(-fly_walk,-fly_walk),
		ShogiPoint(0,-1),
		ShogiPoint(fly_walk,-fly_walk),

		ShogiPoint(-1,0),
		ShogiPoint(1,0),

		ShogiPoint(-fly_walk,fly_walk),
		ShogiPoint(0,1),
		ShogiPoint(fly_walk,fly_walk)
	};

	constexpr ShogiPieceMove ryuo_walk{
		ShogiPoint(-1,-1),
		ShogiPoint(0,-fly_walk),
		ShogiPoint(1,-1),

		ShogiPoint(-fly_walk,0),
		ShogiPoint(fly_walk,0),

		ShogiPoint(-1,1),
		ShogiPoint(0,fly_walk),
		ShogiPoint(1,1)
	};

	constexpr ShogiPieceMove kakugyo_walk{
		ShogiPoint(-fly_walk,-fly_walk),
		ShogiPoint(0,0),
		ShogiPoint(fly_walk,-fly_walk),

		ShogiPoint(0,0),
		ShogiPoint(0,0),

		ShogiPoint(-fly_walk,fly_walk),
		ShogiPoint(0,0),
		ShogiPoint(fly_walk,fly_walk)
	};

	constexpr ShogiPieceMove hisha_walk{
		ShogiPoint(0,0),
		ShogiPoint(0,-fly_walk),
		ShogiPoint(0,0),

		ShogiPoint(-fly_walk,0),
		ShogiPoint(fly_walk,0),

		ShogiPoint(0,0),
		ShogiPoint(0,fly_walk),
		ShogiPoint(0,0)
	};

	constexpr ShogiPieceMove keima_walk{
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(-1,2),
		ShogiPoint(0,0),
		ShogiPoint(1,2)
	};

	constexpr ShogiPieceMove kyosha_walk{
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,fly_walk),
		ShogiPoint(0,0)
	};
	constexpr ShogiPieceMove ginsho_walk{
		ShogiPoint(-1,-1),
		ShogiPoint(0,0),
		ShogiPoint(1,-1),

		ShogiPoint(0,0),
		ShogiPoint(0,0),

		ShogiPoint(-1,1),
		ShogiPoint(0,1),
		ShogiPoint(1,1)
	};
	constexpr ShogiPieceMove kinsho_walk{
		ShogiPoint(0,0),
		ShogiPoint(0,-1),
		ShogiPoint(0,-0),

		ShogiPoint(-1,0),
		ShogiPoint(1,0),

		ShogiPoint(-1,1),
		ShogiPoint(0,1),
		ShogiPoint(1,1)
	};
	constexpr ShogiPieceMove fuhyo_walk{
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,0),
		ShogiPoint(0,1),
		ShogiPoint(0,0)
	};

}
#endif //Included Dungeon Template Library