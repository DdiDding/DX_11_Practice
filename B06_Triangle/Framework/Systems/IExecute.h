#pragma once

class IExecute
{
public:
	virtual void Initialize() = 0;
	//��Ƽ������ ������ ����Ҷ�
	virtual void Ready() = 0;

	virtual void Destroy() = 0;

	virtual void Update() = 0;
	//RTV���ö� �ٽ�
	virtual void PreRender() = 0;

	virtual void Render() = 0;
	//UI�� 2d ������ ����� ����Ҷ� 
	virtual void PostRender() = 0;
	//ȭ��ũ�� ��ȭ �ɶ�
	virtual void ResizeScreen() = 0;
};