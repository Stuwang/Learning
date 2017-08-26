#include <iostream>
#include <memory>

#define NO_TO_USED -1
#define USED  -1
#define NO_NEXT  -2

class IdMaster{

public:
	
	static const short NULL_ID = -1;

	IdMaster(){
		head_ = 0;
		id_.reset(new short[1024]());
		for (int i = 0; i < 1024; ++i)
		{
			id_[i] = i+1;
		}
		id_[1024-1] = NULL_ID;
	};
	IdMaster(int size){
		head_ = 0;
		id_.reset(new short[size]());
		for (int i = 0; i < size; ++i)
		{
			id_[i] = i+1;
		}
		id_[size-1] = NULL_ID;
	};
	~IdMaster(){
	}
	short GetId(){
		if( head_ == NULL_ID){
			return -1;
		}
		short i = head_;
		head_ = id_[head_];
		id_[i] = i;
		return i;
	}
	void PutId(short in){
		id_[in] = head_;
		head_ = in;
	}

private:
	short head_;
	std::unique_ptr<short[]> id_;

	IdMaster(const IdMaster&);
	IdMaster& operator=(const IdMaster&);

};

int main(){
	IdMaster idm(10);
	while(true){
		auto ret = idm.GetId();
		if(ret != -1){
			std::cout << "Get Id " << ret << std::endl;
		}else{
			std::cout << "No To Use " << std::endl ;
			break;
		}
	}

	for(int i=0;i<10;i++){
		idm.PutId(i);
	}

	std::cout << "-================" << std::endl;

	while(true){
		auto ret = idm.GetId();
		if(ret != -1){
			std::cout << "Get Id " << ret << std::endl;
		}else{
			std::cout << "No To Use " << std::endl ;
			break;
		}
	}
}
