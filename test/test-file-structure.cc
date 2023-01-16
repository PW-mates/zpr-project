//
// Created by andrii on 11.12.22.
//
#include <gtest/gtest.h>
#include "zpr_sync/File.h"
#include "zpr_sync/Directory.h"

namespace zpr_sync
{
    TEST(FileTest, Constructor)
    {
        File file1("/path", "/path/full_path.txt", "flag", "full_path", "txt", "100", "2023-01-01 10:00:00", FileType::FILE);
        EXPECT_EQ(file1.path, "/path");
        EXPECT_EQ(file1.full_path, "/path/full_path.txt");
        EXPECT_EQ(file1.flag, "flag");
        EXPECT_EQ(file1.name, "full_path");
        EXPECT_EQ(file1.extension, "txt");
        EXPECT_EQ(file1.size, "100");
        EXPECT_EQ(file1.last_modified, "2023-01-01 10:00:00");
        EXPECT_EQ(file1.type, FileType::FILE);

        File file2("/path", "/path/full_path.txt", "flag", ".hidden_file", "txt", "100", "2023-01-01 10:00:00", FileType::FILE);
        EXPECT_EQ(file2.hidden, true);
    }

    TEST(FileTest, FileType)
    {
        File file1("/path", "/path/full_path.txt", "flag", "full_path", "txt", "100", "2023-01-01 10:00:00", FileType::DIRECTORY);
        EXPECT_EQ(file1.type, FileType::DIRECTORY);

        File file2("/path", "/path/full_path.txt", "flag", "full_path", "txt", "100", "2023-01-01 10:00:00", FileType::SYMLINK);
        EXPECT_EQ(file2.type, FileType::SYMLINK);

        File file3("/path", "/path/full_path.txt", "flag", "full_path", "txt", "100", "2023-01-01 10:00:00", FileType::UNKNOWN);
        EXPECT_EQ(file3.type, FileType::UNKNOWN);
    }

    TEST(DirectoryTest, Constructor) {
        zpr_sync::Directory dir("/path/to/dir", "flag", "dir_name", "2023-01-01 10:00:00", {}, {});
        EXPECT_EQ(dir.path, "/path/to/dir");
        EXPECT_EQ(dir.flag, "flag");
        EXPECT_EQ(dir.name, "dir_name");
        EXPECT_EQ(dir.last_modified, "2023-01-01 10:00:00");
        EXPECT_EQ(dir.sub_dir.size(), 0);
        EXPECT_EQ(dir.files.size(), 0);
        EXPECT_FALSE(dir.hidden);
    }

    TEST(DirectoryTest, add_sub_dir) {
        zpr_sync::Directory dir("/path/to/dir", "flag", "dir_name", "2023-01-01 10:00:00", {}, {});
        zpr_sync::Directory sub_dir("/path/to/dir/sub_dir", "flag", "sub_dir_name", "2023-01-01 10:00:00", {}, {});
        dir.add_sub_dir(&sub_dir);
        EXPECT_EQ(dir.sub_dir.size(), 1);
        EXPECT_EQ(dir.sub_dir[0], &sub_dir);
    }

    TEST(DirectoryTest, add_file) {
        zpr_sync::File file("/path/to/file", "full_path", "flag", "file_name", "extension", "size", "2023-01-01 10:00:00", zpr_sync::FileType::FILE);
        zpr_sync::Directory dir("/path/to/dir", "flag", "dir_name", "2023-01-01 10:00:00", {}, {});
        dir.add_file(&file);
        EXPECT_EQ(dir.files.size(), 1);
        EXPECT_EQ(dir.files[0], &file);
    }

}
