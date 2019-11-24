class MazeFactory
{
private:
	static MazeFactory* _pInstance;
protected:
	MazeFactory() {};
public:
	static MazeFactory* Instance();
	//existing maze interface goes here
};
