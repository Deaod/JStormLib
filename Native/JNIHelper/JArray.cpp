#include "JArray.h"



template<typename arrayType>
JNIH_EXPORT JArray<arrayType>::JArray(JniEnv env) : _env(env) {

}

template<typename arrayType>
JNIH_EXPORT JArray<arrayType>::JArray(JniEnv env, jsize length) : _env(env) {
    arrayType array = JArrayType::create(length);
    this->get(array);
}

template<typename arrayType>
JNIH_EXPORT JArray<arrayType>::JArray(JniEnv env, arrayType array) : _env(env) {
    this->get(array);
}

template<typename arrayType>
JNIH_EXPORT JArray<arrayType>::JArray(JniEnv env, arrayType array, jsize offset, jsize length) : _env(env) {
    this->get(array, offset, length);
}

template<typename arrayType>
JNIH_EXPORT JArray<arrayType>::JArray(JArray<arrayType>& other) : _env(other._env) {
    switch(other._filled) {
    case JArraySource::REGION:
        this->get(other._array, other._offset, other._length);
        break;

    case JArraySource::ELEMENTS:
        this->get(other._array);
        break;
    }
}

template<typename arrayType>
JNIH_EXPORT JArray<arrayType>& JArray<arrayType>::operator=(JArray<arrayType>& other) {
    this->release();
    this->_env = other._env;
    switch(other._filled) {
    case JArraySource::REGION:
        this->get(other._array, other._offset, other._length);
        break;

    case JArraySource::ELEMENTS:
        this->get(other._array);
        break;
    }
}

template<typename arrayType>
JNIH_EXPORT JArray<arrayType>::~JArray() {
    this->release();
}

template<typename arrayType>
JNIH_EXPORT void JArray<arrayType>::get(arrayType array) {
    this->_data = JArrayType<arrayType>::get(_env, array);
    this->_filled = JArraySource::ELEMENTS;
    this->_array = array;
}

template<typename arrayType>
JNIH_EXPORT void JArray<arrayType>::get(arrayType array, jsize offset, jsize length) {
    JArrayType<arrayType>::getRegion(&(this->_env), array, offset, length, this->_data);
    this->_filled = JArraySource::REGION;
    this->_array = array;
    this->_offset = offset;
    this->_length = length;
}

template<typename arrayType>
JNIH_EXPORT void JArray<arrayType>::release() {
    switch(this->_filled) {
    case JArraySource::ELEMENTS:
        JArrayType<arrayType>::set(&(this->_env), this->_array, this->_data, JArrayAction::RELEASE);
        break;

    case JArraySource::REGION:
        JArrayType<arrayType>::setRegion(&(this->_env), this->_array, this->_offset, this->_length, this->_data);
        break;
    }
    this->_filled = JArraySource::NONE;
}

template<typename arrayType>
JNIH_EXPORT void JArray<arrayType>::commit() {
    switch(this->_filled) {
    case JArraySource::ELEMENTS:
        JArrayType<arrayType>::set(&(this->_env), this->_array, this->_data, JArrayAction::COMMIT);
        break;

    case JArraySource::REGION:
         JArrayType<arrayType>::setRegion(&(this->_env), this->_array, this->_offset, this->_length, this->_data);
        break;
    }
}

template<typename arrayType>
JNIH_EXPORT void JArray<arrayType>::abort() {
    switch(this->_filled) {
    case JArraySource::ELEMENTS:
        JArrayType<arrayType>::set(&(this->_env), this->_array, this->_data, JArrayAction::ABORT);
        break;
    }
    this->_filled = JArraySource::NONE;
}

template<typename arrayType>
JNIH_EXPORT typename JArray<arrayType>::JType* JArray<arrayType>::getData() {
    return this->_data;
}

template<typename arrayType>
JNIH_EXPORT arrayType JArray<arrayType>::getArray() {
    return this->_array;
}

template<typename arrayType>
JNIH_EXPORT jsize JArray<arrayType>::getLength() {
    return this->_length;
}
