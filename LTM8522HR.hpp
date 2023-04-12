#ifndef __LTM8522HR_H__
#define __LTM8522HR_H__

class LTM8522HR 
{
public:

	LTM8522HR();
	LTM8522HR(const LTM8522HR&) = default;
	LTM8522HR(LTM8522HR&&) = default;
	LTM8522HR& operator=(const LTM8522HR&);
	LTM8522HR& operator=(LTM8522HR&&);

	~LTM8522HR();
};

#endif // __LTM8522HR_H__