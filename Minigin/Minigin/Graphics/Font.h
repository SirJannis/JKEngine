#pragma once

struct _TTF_Font;
namespace JKEngine
{
	/**
	 * Simple RAII wrapper for an _TTF_Font
	 */
	class Font
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
		
		const std::string& GetPath()const { return m_Path; }
		const unsigned int GetSize() const { return m_Size; }

	private:
		std::string m_Path;
		_TTF_Font* m_Font;
		unsigned int m_Size;
	};
}
