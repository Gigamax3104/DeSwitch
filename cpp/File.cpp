#include	"../h/File.h"
#include	"../h/ErrorMessage.h"

#include	<cstring>
#include	<utility>
#include	<algorithm>

using namespace DeSwitch;

File::File(const std::string& file_name) : m_size(NULL), m_file_name(file_name){
	std::fstream file(file_name, std::ios::binary | std::ios::out | std::ios::trunc); //バイナリモードでファイルを開く(読み込み専用のifstream)
	if (!file.is_open()) return;

	file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	if (!file.read((char*)m_buf.data(), m_size)) return;

	m_file = std::move(file);

	file.close();
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
	try { if (m_file.is_open()) throw -1; }
	catch(int value) { throw ErrorMassage("Error::ファイルを読み込めませんでした。"); }

	m_file << data;
}

template <typename T> void File::Load(T* data) {
	try { if (m_file.is_open()) throw -1; }
	catch(int value) { throw ErrorMassage("Error::ファイルを読み込めませんでした。"); }

	*data << m_file;
}

ImageFile::ImageFile(const std::string& file_name) : File(file_name){
	size_t divide_format = file_name.find_last_of(".");
	if (divide_format == std::string::npos) return;

	std::string format = file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "png" || format == "jpg" || format == "bmp") m_image_file = LoadGraph((const TCHAR*)&file_name);
}

int ImageFile::Base_LoadFile(const std::string& file_name, bool get) {
	std::fstream file(file_name, std::ios::binary | std::ios::out | std::ios::trunc); //バイナリモードでファイルを開く(読み込み専用のifstream)
	try { if (!file.is_open()) throw -1; }
	catch (int value) { throw ErrorMassage("Error::ファイルを読み込めませんでした。"); }

	file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	try { if (!file.read((char*)m_buf.data(), m_size)) throw -1; }
	catch (int value) { throw ErrorMassage("Error::ファイルのサイズを確保できませんでした。"); }

	m_file = std::move(file);

	file.close();

	if (m_image_file != -1) DeleteGraph(m_image_file); //既に画像が設定されていた場合、メモリから削除する。

	size_t divide_format = file_name.find_last_of(".");
	try { if (divide_format == std::string::npos) throw -1; }
	catch (int value) { throw ErrorMassage("Error::ファイルの形式が読み込めませんでした。"); }

	std::string format = file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	try {
		if (format == "png" || format == "jpg" || format == "bmp") m_image_file = LoadGraph((const TCHAR*)&file_name);
		else throw -1;
	}
	catch (int value) { throw ErrorMassage("Error::ファイルの形式が画像ではありませんでした。"); }

	return get ? m_image_file : NULL;
}

void ImageFile::operator=(const ImageFile& other) {
	if (this != &other) {
		if(other.m_file_name != "\0") LoadFile(other.m_file_name);
		this->m_buf = other.m_buf;
		this->m_size = other.m_size;
	}
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
	if (divide_format == std::string::npos) return;

	std::string format = file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "mp4") m_movie_file = LoadGraph((const TCHAR*)&file_name);

}
int MovieFile::Base_LoadFile(const std::string& file_name, bool get) {
	std::fstream file(file_name, std::ios::binary | std::ios::out | std::ios::trunc); //バイナリモードでファイルを開く(読み込み専用のifstream)
	try { if (!file.is_open()) throw - 1; }
	catch (int value) { throw ErrorMassage("Error::ファイルを読み込めませんでした。"); }

	file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	try { if (!file.read((char*)m_buf.data(), m_size)) throw -1; }
	catch (int value) { throw ErrorMassage("Error::ファイルのサイズを確保できませんでした。"); }

	m_file = std::move(file);

	file.close();

	if (m_movie_file != -1) DeleteGraph(m_movie_file); //既に映像が設定されている場合、メモリから削除する。

	size_t slash = file_name.find_last_of("/\\"); //スラッシュの後のファイルサイズを求める
	std::string name = (slash == std::string::npos) ? file_name : file_name.substr(slash + 1); // ファイル名/データ名であればスラッシュの後を切り出す

	std::string tempPath = "temp_" + name;

	std::ofstream outFile(tempPath, std::ios::binary);
	try { if (!outFile.is_open()) throw -1; } // ディスク書き込み失敗時のエラーチェック
	catch (int value) { throw ErrorMassage("Error::ディスクからファイルを読み込めませんでした。"); }

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