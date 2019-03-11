#include <iostream>
#include <vector>

using namespace std;

class Layer
{
public:
    bool oneBlobOnly;
    bool inPlace;
    string name;
    int input;

public:
    bool isInput;

public:
    Layer();
    ~Layer();
    virtual int forward(int& in, int& out);

};

Layer::Layer()
{
    cout << "Layer construct" << endl;
    isInput = false;
    input = 0;
}

Layer::~Layer()
{
    cout << "Layer dis construct" << endl;
}

int Layer::forward(int& in, int& out)
{
    cout << "Layer forward" << endl;
}

class Add100Layer : public Layer
{

public:
    Add100Layer();
    Add100Layer(bool, bool);
    ~Add100Layer();
    int forward(int& i, int& o);
};

Add100Layer::Add100Layer()
{

}

Add100Layer::Add100Layer(bool one, bool in)
{
    cout << "construct Add 100 Layer" << endl;
    oneBlobOnly = one;
    inPlace = in;
    cout << "one blob only is: " << oneBlobOnly << endl;
}


Add100Layer::~Add100Layer()
{
    cout << "dis construct Add 100 Layer" << endl;
}


int Add100Layer::forward(int& i, int& o)
{
    o = i + 100;
    return 0;
}

class Add500Layer : public Layer
{
public:
    Add500Layer();
    ~Add500Layer();
    int forward(int& i, int& o);

};

Add500Layer::Add500Layer()
{
    cout << "construct Add 500 Layer" << endl;
}

Add500Layer::~Add500Layer()
{
    cout << "disconstruct Add 500 Layer" << endl;
}

int Add500Layer::forward(int& i, int& o)
{
    o = i + 500;
    return 0;
}


class Mul2Layer : public Layer
{
public:
    Mul2Layer();
    ~Mul2Layer();
    int forward(int& i, int& o);
};

Mul2Layer::Mul2Layer()
{
}

Mul2Layer::~Mul2Layer()
{
}

int Mul2Layer::forward(int& i, int& o)
{
    o = i*2;
    return 0;
}

//前向递归推图
int checkForwardLayer(const vector<Layer*>& net, int index)
{
    if(index < 0) {
        cout << "err when check for forward layer" << endl;
        return -1;
    }
    cout << "check Lyaer: " << net.at(index)->name << endl;
    //NCNN工程里的判断是以维度为判断依据，如果没有计算过，那么bolb.dums = 0
    if(net.at(index)->isInput == false) {
        index--;
        checkForwardLayer(net, index);
    }
    return 0;
}

//后向递归forward计算
void doForward(const vector<Layer*>& net, int index, const string outputLayerName, int input, int& finalOutput)
{
    int result = 0;
    cout << "forward input is: " << input << endl;
    if(net.at(index)->name == outputLayerName) {
        cout << "input is: " << input << endl;
        cout << "output layer: " << net.at(index)->name << endl;
        net.at(index)->forward(input, result);
        cout << "result is: " << result << endl;
        finalOutput = result;
        return;
    }

    cout << "layer: " << net.at(index)->name << " forward" << endl;
    //调用具体层的forward计算
    net.at(index)->forward(input, result);
    index++;
    doForward(net, index, outputLayerName, result, finalOutput);
    ///return 0;
}

int main()
{

    //创建网络并喂数据
    vector<Layer*> net(0);
    
    Add100Layer* mAdd100Layer = new Add100Layer();
    mAdd100Layer->name = "L1";
    mAdd100Layer->isInput = true;   //input
    mAdd100Layer->input = 10;
   
    net.push_back(mAdd100Layer);   

    Add500Layer* mAdd500Layer = new Add500Layer();
    mAdd500Layer->name = "L2";
    net.push_back(mAdd500Layer);

    Mul2Layer* mMul2Layer = new Mul2Layer();
    mMul2Layer->name = "L3";
    net.push_back(mMul2Layer);

    int numLayer = net.size() - 1;
    cout << "net size is: " << net.size() << endl;

    //往前推图，直到数据输入的地方
    int startForwardIndex = checkForwardLayer(net, numLayer);
    cout << "start forward Layer Index is: " << startForwardIndex << endl;

    int result = 0;

    //从数据输入的地方逐层计算
    doForward(net, startForwardIndex, "L3", net.at(startForwardIndex)->input, result);
    cout << "result is: " << result  << endl;

    //delete mAdd100Layer;
    return 0;
}


