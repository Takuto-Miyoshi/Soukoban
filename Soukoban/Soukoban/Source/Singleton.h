
#ifndef SINGLETON_H
#define SINGLETON_H

// シングルトンデザインパターン
template < class T >
class Singleton{
protected:
	Singleton(){}			// コンストラクタ抑制
	virtual ~Singleton(){}	// デストラクタ抑制

private:
	// 自分自身のポインタ変数(自分自身の唯一の実態)
	static T* pInstance;

public:
	// 実態を作る関数
	static void CreateInstance(){
		// 既に作られているなら新しく作らないことを保証する
		if( pInstance == nullptr )pInstance = new T();
	}

	static void DestroyInstance(){
		delete pInstance;
		pInstance = nullptr;
	}

	static T* GetInstance(){
		return pInstance;
	}

	static bool IsNull(){
		return ( pInstance == nullptr );
	}
};

template < class T >
T* Singleton<T>::pInstance = nullptr;

#endif // !SINGLETON_H

