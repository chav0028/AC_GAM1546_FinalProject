#ifndef __POOL__H__
#define __POOL__H__

#include <vector>

/*Temlate classs to easily manage object/memory pooling.*/
template<class T>
class Pool
{

public:
	Pool(unsigned int numberObjects);
	~Pool();

	void deactivateObject(T* object);
	T* getActivateObject();
	void addNewObjectsToPool(unsigned int numberObjects);

    T* getInactiveObject(unsigned int aIndex);

	int getActiveObjectIndex(T* object);
    int getInactiveObjectIndex(T * object);

	std::vector<T*> getCurrentlyActiveObjects();
    std::vector<T*> getCurrentlyInactiveObjects();

private:
	std::vector<T*>m_ActiveObjects;
	std::vector <T*>m_InactiveObjects;
};

template<class T>
inline Pool<T>::Pool(unsigned int numberObjects)
{
	addNewObjectsToPool(numberObjects);//Create the number of objects
}

template<class T>
inline Pool<T>::~Pool()
{
	//Go through all objects
	while (m_ActiveObjects.empty() == false)
	{
		delete m_ActiveObjects.back();//Delete last object
		m_ActiveObjects.pop_back();//Remove it from vector
	}

	while (m_InactiveObjects.empty() == false)
	{
		delete m_InactiveObjects.back();//Delete last object
		m_InactiveObjects.pop_back();//Remove it from vector
	}
}

template<class T>
inline void Pool<T>::deactivateObject(T * object)
{
	m_InactiveObjects.push_back(object);//Add object back to inactive list


	int index = getActiveObjectIndex(object);
	if (index != -1)//if the object was find in the active objects
	{
		m_ActiveObjects.erase(m_ActiveObjects.begin() + index);//Remove element from active objects
	}
}

template<class T>
inline T * Pool<T>::getActivateObject()
{
	//If we  have aN inactive object left
	if (m_InactiveObjects.empty() == false)
	{
		T* object = m_InactiveObjects.back();//Get the object from the back of the inactive list
		m_InactiveObjects.pop_back();//Remove the object from inactive list

		if (object != nullptr)
		{
			m_ActiveObjects.push_back(object);//Add the object to active list

			return object;//Return the object
		}
	}
	//We could create more objects here if the inactive list is empty

	return nullptr;//Return nullptr
}

//Function do return an inactive object, doesn't remove it from inactive list or activate the object
template<class T>
inline T * Pool<T>::getInactiveObject(unsigned int aIndex)
{
    //If we  have aN inactive object left
    if (m_InactiveObjects.empty() == false)
    {
        if (m_InactiveObjects.size() < aIndex)
        {
            T* object = m_InactiveObjects.at(aIndex);//Get the object from the back of the inactive list

            if (object != nullptr)//If it is a valid object
            {
                return object;//Return the object
            }
        }
    }
    //We could create more objects here if the inactive list is empty

    return nullptr;//Return nullptr
}

template<class T>
inline void Pool<T>::addNewObjectsToPool(unsigned int numberObjects)
{
	for (unsigned int i = 0; i < numberObjects; i++)
	{
		m_InactiveObjects.push_back(new T(this));//Create an object and set that it belongs to this pool
	}
}

template<class T>
inline int Pool<T>::getActiveObjectIndex(T * object)
{
	//Check that there is a valid object
	if (object != nullptr)
	{
		//Look for the object in the active projectiles
		for (unsigned int i = 0; i < m_ActiveObjects.size(); i++)
		{
			//If the object is find
			if (m_ActiveObjects.at(i) == object)
			{
				return i;//Return the position at it was find
			}
		}
	}

	return -1;//If it wasn't find , return -1 to indicate an error
}

template<class T>
inline int Pool<T>::getInactiveObjectIndex(T * object)
{
    //Check that there is a valid object
    if (object != nullptr)
    {
        //Look for the object in the active projectiles
        for (unsigned int i = 0; i < m_InactiveObjects.size(); i++)
        {
            //If the object is find
            if (m_InactiveObjects.at(i) == object)
            {
                return i;//Return the position at it was find
            }
        }
    }

    return -1;//If it wasn't find , return -1 to indicate an error
}


template<class T>
inline std::vector<T*> Pool<T>::getCurrentlyActiveObjects()
{
	return m_ActiveObjects;
}

template<class T>
inline std::vector<T*> Pool<T>::getCurrentlyInactiveObjects()
{
    return m_InactiveObjects;
}

#endif