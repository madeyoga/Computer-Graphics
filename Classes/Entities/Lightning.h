#pragma once
class Lightning {
public:
	
	Vector __position;

	Lightning() {

	}
	
	void set(Lightning _light) {
		__position.x = _light.__position.x;
		__position.y = _light.__position.y;
		__position.z = _light.__position.z;
	}

	void set_light(float x, float y, float z) {
		__position.x = x;
		__position.y = y;
		__position.z = z;
	}

};