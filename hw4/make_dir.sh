mkdir -p top_dir #create toplevel directory

mkdir -p top_dir/sub_dir1 #subdirectories 
mkdir -p top_dir/sub_dir2

truncate -s 3K top_dir/3kfile.txt
truncate -s 5k top_dir/5kfile.txt

#creating 4 files per each subdir

truncate -s 10k top_dir/sub_dir1/10kfile_sub_dir1.txt
truncate -s 10k top_dir/sub_dir2/10kfile_sub_dir2.txt

truncate -s 5k top_dir/sub_dir1/5kfile_sub_dir1.txt
truncate -s 5k top_dir/sub_dir2/5kfile_sub_dir2.txt

truncate -s 8k top_dir/sub_dir1/8kfile_sub_dir1.txt
truncate -s 8k top_dir/sub_dir2/8kfile_sub_dir2.txt

truncate -s 1k top_dir/sub_dir1/1kfile_sub_dir1.txt
truncate -s 1k top_dir/sub_dir2/1kfile_sub_dir2.txt

#change perms
chmod -w top_dir/3kfile.txt
chmod -w top_dir/sub_dir1/10kfile_sub_dir1.txt
chmod -w top_dir/sub_dir2/10kfile_sub_dir2.txt

