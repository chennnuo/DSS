#ifndef __COSMETICENGINE_H__
#define __COSMETICENGINE_H__

#include "StackingTasks.h"

class CCosmeticStats
{
public :
	int			m_lNrTotalPixels;
	int			m_lNrDetectedHotPixels;
	int			m_lNrDetectedColdPixels;

private :
	void		CopyFrom(const CCosmeticStats & cs)
	{
		m_lNrTotalPixels		= cs.m_lNrTotalPixels;
		m_lNrDetectedHotPixels	= cs.m_lNrDetectedHotPixels;
		m_lNrDetectedColdPixels = cs.m_lNrDetectedColdPixels;
	};
public :
	CCosmeticStats()
	{
		m_lNrTotalPixels = 0;
		m_lNrDetectedHotPixels = 0;
		m_lNrDetectedColdPixels = 0;
	};

	CCosmeticStats(const CCosmeticStats & cs)
	{
		CopyFrom(cs);
	};

	~CCosmeticStats() {};

	CCosmeticStats & operator = (const CCosmeticStats & cs)
	{
		CopyFrom(cs);
		return (*this);
	};
};

std::shared_ptr<CMemoryBitmap> ApplyCosmetic(std::shared_ptr<CMemoryBitmap> pBitmap, const CPostCalibrationSettings& pcs, CDSSProgress* const pProgress);
void SimulateCosmetic(std::shared_ptr<CMemoryBitmap> pBitmap, const CPostCalibrationSettings& pcs, CCosmeticStats& cs, CDSSProgress* const pProgress);

#endif