
#include <type_traits>

template<typename T>
struct HandleTraits
{
    using value_type = T;

    static T invalid() noexcept
    {
        return nullptr;
    }
};

template<typename Traits>
class Handle
{

    using value_type = decltype(Traits::invalid());
    value_type m_value;

    void close() noexcept
    {
        if (*this)
        {
            Traits::close(m_value);
        }
    }

  public:
    
    Handle(Handle const &) = delete;
    Handle &operator=(Handle const &) = delete;

    explicit Handle(value_type value = Traits::Invalid) noexcept : m_value(value)
    {
    }

    Handle(Handle&& other) noexcept 
        : m_value(other.detach())
    {
    
    }

    Handle operator=(Handle&& other)
    {
        if (this != &other)
        {
            reset(other.detach());
        }

        return *this;
    }

    value_type detach() noexcept
    {
        auto value = m_value;
        m_value = Traits::invalid();

        return value;
    }

    ~Handle() noexcept
    {
        close();
    }

    explicit operator bool() const noexcept
    {
        return m_value != Traits::invalid();
    }

    value_type get() const noexcept
    {
        return m_value;
    }

    value_type *set() noexcept
    {
        return &m_value;
    }

    bool reset(value_type value = Traits::invalid()) noexcept
    {
        if (m_value != value)
        {
            close();
            m_value = value;
        }
        
        return static_cast<bool>(*this);
    }

    void swap(Handle<Traits>& other) noexcept
    {
        value_type temp = m_value;
        m_value = other.m_value;
        other.m_value = temp;
    }
};

template<typename Traits>
void swap(Handle<Traits>& lhs, Handle<Traits>& rhs) noexcept
{
    lhs.swap(rhs);
}

template<typename Traits> 
bool operator==(Handle<Traits> const& lhs, Handle<Traits> const& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template<typename Traits> 
bool operator!=(Handle<Traits> const& lhs, Handle<Traits> const& rhs) noexcept
{
    return !(lhs == rhs);
}