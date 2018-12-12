#pragma once

class Face 
{
public:
	vector<int> vertex_indices, normal_indices, uv_indices;
	int *v, *vt, *vn;
	int length;
	Face() 
	{

	}
	Face(vector<int> &v1, vector<int> &v2, vector<int> &v3) 
	{
		vertex_indices = v1;
		normal_indices = v2;
		uv_indices = v3;
	}
	Face(int n) 
	{
		length = n;
		v = new int[length];
		vt = new int[length];
		vn = new int[length];
	}
	void LoadFace(int arr[], int arr2[], int arr3[]) 
	{
		for (int i = 0; i < length; i++)
		{
			v[i] = arr[i];
			vt[i] = arr2[i];
			vn[i] = arr3[i];
		}
	}
};
