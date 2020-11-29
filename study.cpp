#include <iostream>
using namespace std;

// 基类 衣服
class Clothe
{
public:
    virtual void Show() = 0;
    virtual ~Clothe() {}
};

// 耐克衣服
class NiKeClothe : public Clothe
{
public:
    void Show()
    {
        std::cout << "我是耐克衣服，时尚我最在行！" << std::endl;
    }
};

// 基类 鞋子
class Shoes
{
public:
    virtual void Show() = 0;
    virtual ~Shoes() {}
};

// 耐克鞋子
class NiKeShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是耐克球鞋，让你酷起来！" << std::endl;
    }
};

// 总厂
class Factory
{
public:
    virtual Shoes *CreateShoes() = 0;
	virtual Clothe *CreateClothe() = 0;
    virtual ~Factory() {}
};

// 耐克生产者/生产链
class NiKeProducer : public Factory
{
public:
    Shoes *CreateShoes()
    {
        return new NiKeShoes();
    }
	
	Clothe *CreateClothe()
    {
        return new NiKeClothe();
    }
};

int main()
{
    // ================ 生产耐克流程 ==================== //
    // 鞋厂开设耐克生产线
    Factory *niKeProducer = new NiKeProducer();
    
	// 耐克生产线产出球鞋
    Shoes *nikeShoes = niKeProducer->CreateShoes();
	// 耐克生产线产出衣服
    Clothe *nikeClothe = niKeProducer->CreateClothe();
    
	// 耐克球鞋广告喊起
    nikeShoes->Show();
	// 耐克衣服广告喊起
    nikeClothe->Show();
	
    // 释放资源
    delete nikeShoes;
	delete nikeClothe;
    delete niKeProducer;


    return 0;
}

#if 0
// 工厂方法模式
class Shoes
{
public:
    virtual ~Shoes() {}
    virtual void Show() = 0;
};

// 耐克鞋子
class NiKeShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
    }
};

// 阿迪达斯鞋子
class AdidasShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是阿迪达斯球鞋，我的广告语:Impossible is nothing" << std::endl;
    }
};

// 李宁鞋子
class LiNingShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是李宁球鞋，我的广告语：Everything is possible" << std::endl;
    }
};


// 总鞋厂
class ShoesFactory
{
public:
    virtual Shoes *CreateShoes() = 0;
    virtual ~ShoesFactory() {}
};

// 耐克生产者/生产链
class NiKeProducer : public ShoesFactory
{
public:
    Shoes *CreateShoes()
    {
        return new NiKeShoes();
    }
};

// 阿迪达斯生产者/生产链
class AdidasProducer : public ShoesFactory
{
public:
    Shoes *CreateShoes()
    {
        return new AdidasShoes();
    }
};

// 李宁生产者/生产链
class LiNingProducer : public ShoesFactory
{
public:
    Shoes *CreateShoes()
    {
        return new LiNingShoes();
    }
};

int main()
{
    // ================ 生产耐克流程 ==================== //
    // 鞋厂开设耐克生产线
    ShoesFactory *niKeProducer = new NiKeProducer();
    // 耐克生产线产出球鞋
    Shoes *nikeShoes = niKeProducer->CreateShoes();
    // 耐克球鞋广告喊起
    nikeShoes->Show();
    // 释放资源
    delete nikeShoes;
    delete niKeProducer;

    // ================ 生产阿迪达斯流程 ==================== //
    // 鞋厂开设阿迪达斯生产者
    ShoesFactory *adidasProducer = new AdidasProducer();
    // 阿迪达斯生产线产出球鞋
    Shoes *adidasShoes = adidasProducer->CreateShoes();
    // 阿迪达斯球鞋广喊起
    adidasShoes->Show();
    // 释放资源
    delete adidasShoes;
    delete adidasProducer;

    return 0;
}
#endif
#if 0 
// 简单工厂模式

// 鞋子抽象类
class Shoes
{
public:
    virtual ~Shoes() {}
    virtual void Show() = 0;
};

// 耐克鞋子
class NiKeShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
    }
};

// 阿迪达斯鞋子
class AdidasShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是阿迪达斯球鞋，我的广告语:Impossible is nothing" << std::endl;
    }
};

// 李宁鞋子
class LiNingShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是李宁球鞋，我的广告语：Everything is possible" << std::endl;
    }
};

enum SHOES_TYPE
{
    NiKe,
    LiNing,
    Adidas
};

// 总鞋厂
class ShoesFactory
{
public:
    // 根据鞋子类型创建对应的鞋子对象
    Shoes *CreateShoes(SHOES_TYPE type)
    {
        switch (type)
        {
        case NiKe:
            return new NiKeShoes();
            break;
        case LiNing:
            return new LiNingShoes();
            break;
        case Adidas:
            return new AdidasShoes();
            break;
        default:
            return NULL;
            break;
        }
    }
};

int main()
{
    // 构造工厂对象
    ShoesFactory shoesFactory;

    // 从鞋工厂对象创建阿迪达斯鞋对象
    Shoes *pNikeShoes = shoesFactory.CreateShoes(NiKe);
    if (pNikeShoes != NULL)
    {
        // 耐克球鞋广告喊起
        pNikeShoes->Show();

        // 释放资源
        delete pNikeShoes;
        pNikeShoes = NULL;
    }

    // 从鞋工厂对象创建阿迪达斯鞋对象
    Shoes *pLiNingShoes = shoesFactory.CreateShoes(LiNing);
    if (pLiNingShoes != NULL)
    {
        // 李宁球鞋广告喊起
        pLiNingShoes->Show();

        // 释放资源
        delete pLiNingShoes;
        pLiNingShoes = NULL;
    }

    // 从鞋工厂对象创建阿迪达斯鞋对象
    Shoes *pAdidasShoes = shoesFactory.CreateShoes(Adidas);
    if (pAdidasShoes != NULL)
    {
        // 阿迪达斯球鞋广告喊起
        pAdidasShoes->Show();

        // 释放资源
        delete pAdidasShoes;
        pAdidasShoes = NULL;
    }

    return 0;
}
#endif