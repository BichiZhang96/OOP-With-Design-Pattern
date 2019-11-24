#include "AntiVirus.h"
#include "CompressedFile.h"
#include "EncryptedFile.h"
#include "SendFile.h"

class FileService
{
	AntiVirus anti;
	CompressedFile zip;
	EncryptedFile encrypt;
	SendFile send;

public:
	void MethodA()
	{
		cout << "MethodA:" << endl;
		anti.Operation1();
		zip.Operation2();
		encrypt.Operation3();
		send.Operation4();
	}

	void MethodB()
	{
		cout << "MethodB:" << endl;
		anti.Operation1();
		send.Operation4();
	}
};
