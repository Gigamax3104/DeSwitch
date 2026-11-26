#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include	<fstream>
#include	<experimental/filesystem>
#include	<string>
#include	<vector>
#include	<cstdio>
#include	<memory>
#include	<utility>
#include <type_traits>

#include	"DxLib.h"
#include	"Vector2Int.h"
#include	"ErrorMessage.h"

#define BINARY std::ios::binary
#define IN std::ios::in
#define OUT std::ios::out
#define TRUNC std::ios::trunc

namespace DeSwitch {
  class File {
	public:
		int LoadFile(const std::string& file_name, bool get = false) { return Base_LoadFile(file_name, get); }

		template<typename T> static void Save(const TCHAR* file_name, T&& data); //テンプレートでどの型でもセーブできる
		template<typename T> static void Save_Add(const TCHAR* file_name, const T& data);

		template<typename T> static void Load(const TCHAR* file_name, T* data);

		const std::string& GetFileName() const { return m_file_name; }
		size_t GetSize() const { return m_size; }

		File() : m_size(0), m_buf(NULL) {}
		File(const std::string& file_name);
		File(File&& other) noexcept : m_buf(other.m_buf), m_size(other.m_size) {}

		virtual ~File() { Destroy(); }

		void operator=(File* other);
		File& operator=(File&& other) noexcept; //この代入演算子オーバーロードは、引数が&&であって、一時的なデータやstd::move関数で情報を失ってもよい。
												//noexceptは確実にエラーを発生させないためにする。

		bool operator==(const File& other) const { return this->m_file_name == other.m_file_name; }
	protected:
		size_t m_size;

		std::string m_file_name;

		std::vector<unsigned char> m_buf;

		virtual int Base_LoadFile(const std::string& file_name, bool get) = 0;

	private:
		virtual void Destroy() {}
  };

  class SoundFile : public File {
  public:
	  SoundFile() : File(){}
	  SoundFile(const std::string& file_name);
	  SoundFile(SoundFile&& other) noexcept : File(std::move(other)){}

	  virtual ~SoundFile(){}

	  void operator=(const SoundFile& other);
	  SoundFile& operator=(const SoundFile&& other) noexcept;

	  bool operator==(const SoundFile& other) { return this->m_sound_file == other.m_sound_file; }

	  int GetSoundFile() const { return m_sound_file; }

	  bool CheckSetSoundFile() const { return m_sound_file != -1 && m_sound_file != NULL; }

	  void Destroy() override { if (CheckSetSoundFile()) DeleteSoundMem(m_sound_file); }

  private:
	  int m_sound_file = NULL;

	  int Base_LoadFile(const std::string& file_name, bool get) override;

  };
  class ImageFile : public File {
	public:
		ImageFile() : File() {}
		ImageFile(const std::string& file_name);
		ImageFile(ImageFile&& other) noexcept : File(std::move(other)) {}

		virtual ~ImageFile() {}

		void operator=(const ImageFile& other);
		ImageFile& operator=(const ImageFile&& other) noexcept;

		bool operator==(const ImageFile& other) { return this->m_image_file == other.m_image_file; }

		int GetImageFile() const { return m_image_file; }

		bool CheckSetImageFile() const { return m_image_file != -1 && m_image_file != NULL; }

		void Destroy() override { if (CheckSetImageFile()) { DeleteGraph(m_image_file); m_image_file = -1; } }

	private:
		int m_image_file = NULL;

		int Base_LoadFile(const std::string& file_name, bool get) override;

  };

  class MovieFile : public File {
	public:
		MovieFile() : File() {}
		MovieFile(const std::string& file_name);
		MovieFile(const MovieFile& other) { operator=(other); }

		virtual ~MovieFile() {}

		void operator=(const MovieFile& other);
		MovieFile& operator=(const MovieFile&& other) noexcept;

		bool operator==(const MovieFile& other) { return this->m_movie_file == other.m_movie_file; }

		int GetMovieFile() const { return m_movie_file; }
		int GetFrame() const { return m_movie_frame - 1; }

		bool CheckSetMovieFile() const { return m_movie_file != -1 && m_movie_file != NULL; }

		void Destroy() override { if (CheckSetMovieFile()) { DeleteGraph(m_movie_file); m_movie_file = -1; } }
	private:
		int m_movie_file = NULL;
		int m_movie_frame = NULL;

		int Base_LoadFile(const std::string& file_name, bool get) override;
  };
}

template <typename T> void DeSwitch::File::Save(const TCHAR* file_name, T&& data) {
	std::ofstream file;

	if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
		file.open(file_name); //整数・少数

		if (!file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

		file << std::forward<T>(data);

		file.close();
	}
	else if constexpr (std::is_same_v<std::decay_t<T>, const char*> || std::is_same_v<std::decay_t<T>, const std::string&> || std::is_same_v<std::decay_t<T>, const TCHAR*>) {
		file.open(file_name, std::ios::out | std::ios::binary); //文字列

		if (!file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

		const unsigned char bom[] = { 0xEF, 0xBB, 0xBF }; //日本語用
		file.write(reinterpret_cast<const char*>(bom), sizeof(bom));

		file << std::forward<T>(data);

		file.close();
	}
}

template<typename T> void DeSwitch::File::Save_Add(const TCHAR* file_name, const T& data) {
	std::ofstream file(file_name, std::ios::app);
	if (!file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

	file << data;

	file.close();
}

template <typename T> void DeSwitch::File::Load(const TCHAR* file_name, T* data) {
	std::ifstream file(file_name);
	if (!file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

	while(file >> *data);

	file.close();
}
