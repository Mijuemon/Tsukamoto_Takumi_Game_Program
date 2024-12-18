#include "Substance.h"
#include "Math/MyMath.h"
#include "SubstanceParameter.h"

namespace BOUDAMA
{
	//初期化処理関数
	void Substance::Init(void)
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		pos_ = { static_cast<float>(GetRand(600)),10.0f ,static_cast<float>(GetRand(600)) };
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
		radius_ = SUBSTANCE::RADIUS;

		addScoreNum = SUBSTANCE::ADD_SCORE_NUM;
	}
}
