program rpipe_cmd{
	version v1{
		int rpipe_open(unsigned long cbprog_id, int flag)=1;
		int rpipe_close(int fid)=2;

		int rpipe_write(int fid, unsigned int data_size)=4;
		int rpipe_read(int fid, unsigned int max_size)=5;
	}=1;
}=0x20100160;
