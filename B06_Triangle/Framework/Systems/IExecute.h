#pragma once

class IExecute
{
public:
	virtual void Initialize() = 0;
	//멀티쓰레드 렌더링 얘기할때
	virtual void Ready() = 0;

	virtual void Destroy() = 0;

	virtual void Update() = 0;
	//RTV나올때 다시
	virtual void PreRender() = 0;

	virtual void Render() = 0;
	//UI나 2d 렌더링 결과를 출력할때 
	virtual void PostRender() = 0;
	//화면크기 변화 될때
	virtual void ResizeScreen() = 0;
};