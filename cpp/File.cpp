#include	"../h/File.h"
#include	"../h/ErrorMessage.h"

#include	<cstring>
#include	<utility>
#include	<algorithm>

using namespace DeSwitch;
namespace fs = std::experimental::filesystem; //省略するため用意

File::File(const std::string& file_name) : m_size(NULL){
	if (!file_name.empty()) { //文字列が空でない時
		if (!file_name.front() == '.') { //最初の文字が「.」でない時(ファイル名のみ)
			m_file.open(file_name, BINARY | IN | OUT);

			m_file_name = file_name;
		}
		else if (file_name.find("../") != std::string::npos) { //相対パスの後にファイルがあった時
			fs::path project = fs::path(__FILE__).parent_path(); //このソースコードがあるファイルのパスを返す。(_FILE_がそれ)
			fs::path clean_path = fs::canonical(project / file_name); //canonical→絶対パスへ変換したものを省略されている「../」を除く
			std::string generic = clean_path.generic_string(); //絶対パスでは「＼＼」が区切りとして入っているため、generic_string関数で「/」に戻す
			m_file.open(generic, BINARY | IN | OUT);

			m_file_name = generic;
		}
	}

	if (!m_file.is_open()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込めませんでした。");

	m_file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = m_file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	m_file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	m_file.read((char*)m_buf.data(), m_size);
	if (m_size == NULL) throw ErrorMassage("Error::ファイルのサイズを取得できませんでした。");

	m_file.close();
}

void File::operator=(File* other) {
	if (this != other) {
		this->m_file = std::move(other->m_file);
		this->m_file_name = other->m_file_name;
		this->m_buf = other->m_buf;
		this->m_size = other->m_size;
	}
}

File& File::operator=(File&& other) noexcept {
	if (this != &other) {
		this->m_file = std::move(other.m_file);
		this->m_file_name = other.m_file_name;
		this->m_buf = other.m_buf;
		this->m_size = other.m_size;
	}

	return *this;
}

template <typename T> void File::Save(const T& data) {
	if (m_file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

	m_file << data;
}

template <typename T> void File::Load(T* data) {
	if (m_file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

	*data << m_file;
}

ImageFile::ImageFile(const std::string& file_name) : File(file_name){
	size_t divide_format = m_file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = m_file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "png" || format == "jpeg" || format == "bmp" || format == "dds" || format == "argb" || format == "tga")
		m_image_file = LoadGraph(m_file_name.c_str());
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が画像ではありませんでした。");

	if (m_image_file == -1) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、画像を確保できませんでした。");
}

int ImageFile::Base_LoadFile(const std::string& file_name, bool get) {
	if (!file_name.empty()) { //文字列が空でない時
		if (!(file_name.front() == '.')) { //最初の文字が「.」でない時(ファイル名のみ)
			m_file.open(file_name, BINARY | IN | OUT);

			m_file_name = file_name;
		}
		else if (file_name.find("../") != std::string::npos) { //相対パスの後にファイルがあった時
			fs::path project = fs::path(__FILE__).parent_path(); //このソースコードがあるファイルのパスを返す。(_FILE_がそれ)
			fs::path clean_path = fs::canonical(project / file_name); //canonical→絶対パスへ変換したものを省略されている「../」を除く
			std::string generic = clean_path.generic_string(); //絶対パスでは「＼＼」が区切りとして入っているため、generic_string関数で「/」に戻す
			m_file.open(generic, BINARY | IN | OUT);

			m_file_name = generic;
		}
	}

	if (!m_file.is_open()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込めませんでした。");

	m_file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = m_file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	m_file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	m_file.read((char*)m_buf.data(), m_size);
	if (m_size == NULL) throw ErrorMassage("Error::ファイルのサイズを取得できませんでした。");

	m_file.close();

	size_t divide_format = m_file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = m_file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "png" || format == "jpeg" || format == "bmp" || format == "dds" || format == "argb" || format == "tga")
		m_image_file = LoadGraph(m_file_name.c_str());
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が画像ではありませんでした。");

	if (m_image_file == -1) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、画像を確保できませんでした。");

	return get ? m_image_file : NULL;
}

void ImageFile::operator=(const ImageFile& other) {
	LoadFile(other.m_file_name);
}

ImageFile& ImageFile::operator=(const ImageFile&& other) noexcept {
	if(this != &other) {
		if (other.m_file_name != "\0") LoadFile(other.m_file_name);
		this->m_buf = other.m_buf;
		this->m_size = other.m_size;
	}

	return *this;
}

MovieFile::MovieFile(const std::string& file_name) {
	size_t divide_format = file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::映像ファイルの形式を読み込めませんでした。");

	std::string format = file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "mp4") m_movie_file = LoadGraph((const TCHAR*)&file_name);
	else throw ErrorMassage("Error::ファイルの形式が映像ではありませんでした。");

}
int MovieFile::Base_LoadFile(const std::string& file_name, bool get) {
	std::fstream file(file_name, std::ios::binary | std::ios::out | std::ios::trunc); //バイナリモードでファイルを開く(読み込み専用のifstream)

	if (!file.is_open()) throw ErrorMassage("Error::映像ファイルを読み込めませんでした。");

	file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	file.read((char*)m_buf.data(), m_size);

	if (m_size == NULL) throw ErrorMassage("Error::映像ファイルのサイズを確保できませんでした。");

	m_file = std::move(file);

	file.close();

	if (m_movie_file != -1) DeleteGraph(m_movie_file); //既に映像が設定されている場合、メモリから削除する。

	size_t slash = file_name.find_last_of("/\\"); //スラッシュの後のファイルサイズを求める
	std::string name = (slash == std::string::npos) ? file_name : file_name.substr(slash + 1); // ファイル名/データ名であればスラッシュの後を切り出す

	std::string tempPath = "temp_" + name;

	std::ofstream outFile(tempPath, std::ios::binary);

	if (!outFile.is_open()) throw ErrorMassage("Error::ディスクから映像ファイルを読み込めませんでした。"); // ディスク書き込み失敗時のエラーチェック

	m_size = static_cast<size_t>(outFile.tellp());

	outFile.write((char*)m_buf.data(), File::GetSize());
	outFile.close();

	m_movie_file = OpenMovieToGraph(tempPath.c_str());

	std::remove(tempPath.c_str()); //一時的にファイルを削除

	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	return get ? m_movie_file : NULL;
}

void MovieFile::operator=(const MovieFile& other) {
	if (this != &other) {
		File::LoadFile(other.m_file_name);
		this->m_buf = other.m_buf;
		this->m_size = other.m_size;
	}
}

MovieFile& MovieFile::operator=(const MovieFile&& other) noexcept{
	if (this != &other) {
		File::LoadFile(other.m_file_name);
		this->m_buf = other.m_buf;
		this->m_size = other.m_size;
	}

	return *this;
}

//void MovieFile::Play(Vector2Int startPos, Vector2Int endPos, Vector2Int size) {
//	try{ if (m_movie_file == -1) throw -1; }
//	catch (int value) { throw "Error::映像データが見つかりません。"; }
//
//	PlayMovieToGraph(m_movie_file);
//
//	while (ProcessMessage() == 0 && GetMovieStateToGraph(m_movie_file) == 1)
//		DrawExtendGraph(startPos.x, startPos.y, endPos.x, endPos.y, m_movie_file, TRUE);
//}