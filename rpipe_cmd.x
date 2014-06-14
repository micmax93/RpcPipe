program rpipe_cmd{
	version v1{
		int rpipe_open_r(int cbprog_id)=1;
		int rpipe_open_w(int cbprog_id)=2;
		int rpipe_close()=3;

		int rpipe_write(int data_size)=4;
		int rpipe_read(int max_size)=5;
	}=1;
}=0x20100160;
