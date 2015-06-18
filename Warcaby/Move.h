#pragma once
#include <iostream>

class Move
{
	int oldRow, oldColumn,
		newRow, newColumn,
		attackRow, attackColumn,
		value;
	bool jump;

public:
	Move() : oldRow(), oldColumn(), newRow(), newColumn(), value(), jump(), attackRow(), attackColumn() {}
	Move(int _oldRow, int _oldColumn, int _newRow, int _newColumn, int _value)
		: oldRow(_oldRow), oldColumn(_oldColumn), newRow(_newRow), newColumn(_newColumn), value(_value), jump(false), attackRow(), attackColumn() {}
	Move(int _oldRow, int _oldColumn, int _newRow, int _newColumn, int _value, int _attackRow, int _attackColumn)
		: oldRow(_oldRow), oldColumn(_oldColumn), newRow(_newRow), newColumn(_newColumn), value(_value), jump(true), attackRow(_attackRow), attackColumn(_attackColumn) {}
	~Move() {}

	void setOldRow(int _oldRow) { oldRow = _oldRow; }
	void setOldColumn(int _oldColumn) { oldColumn = _oldColumn; }
	void setNewRow(int _newRow) { newRow = _newRow; }
	void setNewColumn(int _newColumn) { newColumn = _newColumn; }
	void setValue(int _value) { value = _value; }
	void setJump(bool _jump) { jump = _jump; }
	void setAttackRow(int _attackRow) { attackRow = _attackRow; }
	void setAttackColumn(int _attackColumn) { attackColumn = _attackColumn; }

	int getOldRow() const { return oldRow; }
	int getOldColumn() const { return oldColumn; }
	int getNewRow() const { return newRow; }
	int getNewColumn() const { return newColumn; }
	int getValue() const { return value; }
	bool getJump() const { return jump; }
	int getAttackRow() const { return attackRow; }
	int getAttackColumn() const { return attackColumn; }

	bool operator==(const Move &m) { return oldRow == m.oldRow && oldColumn == m.oldColumn && newRow == m.newRow && newColumn == m.newColumn; }
};