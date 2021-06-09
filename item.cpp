
T Item::info() const
{
    return m_info;
}

Item *Item::nextElement() const
{
    return m_nextElement;
}

void Item::setNextElement(Item *nextElement)
{
    m_nextElement = nextElement;
}

void Item::setInfo(const T &info)
{
    m_info = info;
}
