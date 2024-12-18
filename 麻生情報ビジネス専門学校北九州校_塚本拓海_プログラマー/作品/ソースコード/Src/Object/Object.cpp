#include "Object.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//初期化処理関数
	void Object::Init(void)
	{
		//初期化
		handle_ = -1;
		isAlive_ = true;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
	}

	//読み込み処理関数
	void Object::Load(void) {}

	//行動処理関数
	void Object::Step(void) {}

	//描画処理関数
	void Object::Draw(void)
	{
		//生存している場合は描画
		if (isAlive_)
		{
			MV1DrawModel(handle_);
		}
	}

	//破棄処理関数
	void Object::Fin(void)
	{
		//破棄処理
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}
	}

	//当たり判定処理
	void Object::HitCalculation(void)
	{
		//死亡処理
		isAlive_ = false;
		velocity_ = MyMath::ZERO_VECTOR_3D;
	}

	//当たり判定処理
	void Object::HitCalculation(int damage)
	{
		hp_ -= damage;

		if (hp_ <= 0)
		{
			//死亡処理
			isAlive_ = false;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}
	}
}
