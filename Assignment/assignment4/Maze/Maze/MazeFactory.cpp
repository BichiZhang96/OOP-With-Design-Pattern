#include "MazeFactory.h"
MazeFactory* MazeFactory::_pInstance = (MazeFactory*)0;
MazeFactory* MazeFactory::Instance()
{
	if (_pInstance == (MazeFactory*)0)
		_pInstance = new MazeFactory;
	return _pInstance;
}
