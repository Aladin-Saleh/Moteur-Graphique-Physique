#include "BrancheUI.hpp"
#include "Debug.hpp"

namespace Ge
{
	/*BrancheUI::BrancheUI(fs::path p)
	{
		m_path = p;
		for (const auto & entry : fs::directory_iterator(m_path))
		{
			if (fs::is_directory(entry.path()))
			{
				std::cout << entry.path() << std::endl;
				m_BrancheUI.push_back(new BrancheUI(entry.path()));
			}
			else
			{
				m_FeuilleUI.push_back(new FeuilleUI(entry.path()));
			}
		}
	}

	std::vector<BrancheUI*> BrancheUI::getB()
	{
		return m_BrancheUI;
	}

	std::vector<FeuilleUI*> BrancheUI::getF()
	{
		return m_FeuilleUI;
	}

	fs::path BrancheUI::getPath()
	{
		return m_path;
	}

	BrancheUI::~BrancheUI()
	{
		for (BrancheUI* b : m_BrancheUI)
		{
			delete(b);
		}
		for (FeuilleUI* f : m_FeuilleUI)
		{
			delete(f);
		}
		m_BrancheUI.clear();
		m_FeuilleUI.clear();
	}*/
}