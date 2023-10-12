all_files=$(ls compressed_files)

mkdir compressed_files/zip
mkdir compressed_files/rar
mkdir compressed_files/tar.gz
mkdir compressed_files/unknown

# uncompress
for file_name in $all_files; do
    if [[ $file_name =~ .zip$ ]]; then
        unzip compressed_files/$file_name -d compressed_files/zip
    elif [[ $file_name =~ .rar$ ]]; then
        unrar x compressed_files/$file_name compressed_files/rar
    elif [[ $file_name =~ .tar.gz$ ]]; then
        tar -xzf compressed_files/$file_name -C compressed_files/tar.gz
    else
        cp compressed_files/$file_name compressed_files/unknown
    fi
    rm compressed_files/$file_name
done

# wrong_list
for student_id in $(ls compressed_files/unknown); do
    echo $student_id | cut -c1-9 >> "wrong_list"
done

# missing_list
for student_id in $(cat student_id); do
    if !(echo $all_files | grep -q $student_id); then
        echo $student_id >> "missing_list"
    fi
done
