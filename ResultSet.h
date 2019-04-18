/*
 * ResultSet.h
 */

#ifndef RESULTSET_H_
#define RESULTSET_H_

class ResultSet {

private:

	int* results;
	int size;
	int nextPos;
	void resize();

public:

	ResultSet(int size);
	~ResultSet();
	int getSize();
	int* getResults();
	void insert(int value);
	int* combine(ResultSet rs);

};



#endif /* RESULTSET_H_ */
