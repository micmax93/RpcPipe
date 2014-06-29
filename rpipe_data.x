program rpipe_data{
	version v1{
		unsigned int rpipe_put(string data)=1;
		string rpipe_get(unsigned int data_size)=2;
		int rpipe_info(int info_flag)=3;
	}=1;
}=0x30100160;
