#include "inputhandler.h"

InputHandler::InputHandler(QObject *parent) : QObject(parent)
{
    KeyHolder keyEmpty;
    keyEmpty.key = 0;
    keyEmpty.ticks = 0;
    keyEmpty.isPressed = false;
    for(int i = 0; i < MaxKeys; i++)
        m_keys[i] = keyEmpty;
}

void InputHandler::KeyPressEvent(QKeyEvent *event)
{
    KeyHolder holder;
    holder.key = event->key();
    holder.ticks = 0;
    holder.isPressed = true;

    int index = GetKeyIndex(event->key());
    if(index >= 0)
        m_keys[index] = holder;
    else
    {
        index = GetFreeIndex();
        if(index >= 0)
            m_keys[index] = holder;
        else
        {
            index = GetLongestIndex();
            m_keys[index] = holder;
        }
    }

}

void InputHandler::KeyReleaseEvent(QKeyEvent *event)
{
    int index = GetKeyIndex(event->key());
    if(index >= 0)
    {
        m_keys[index].isPressed = false;
    }
}

void InputHandler::UpdateGame(int ticks)
{
    for(int i = 0; i < MaxKeys; i++)
        if(m_keys[i].isPressed)
            m_keys[i].ticks += ticks;
}

bool InputHandler::IsKeyPressed(Qt::Key key, int *timeMSec)
{
    int index = GetKeyIndex(key);
    if(index >= 0)
    {
        *timeMSec = m_keys[index].ticks;
        return m_keys[index].isPressed;
    }
    return false;
}

int InputHandler::GetKeyIndex(int key)
{
    for(int i = 0; i < MaxKeys; i++)
        if(m_keys[i].key == key)
            return i;
    return -1;
}

int InputHandler::GetFreeIndex()
{
    for(int i = 0; i < MaxKeys; i++)
        if(!m_keys[i].isPressed)
            return i;
    return -1;
}


int InputHandler::GetLongestIndex()
{
    int maxTicks = 0;
    int maxIndex = 0;
    for(int i = 0; i < MaxKeys; i++)
        if(m_keys->ticks > maxTicks)
        {
            maxIndex = i;
            maxTicks = m_keys[i].ticks;
        }
    return maxIndex;
}


