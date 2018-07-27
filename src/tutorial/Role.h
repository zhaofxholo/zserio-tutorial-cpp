/**
 * Automatically generated by Zserio C++ extension version 1.0.
 */

#ifndef TUTORIAL_ROLE_H
#define TUTORIAL_ROLE_H

#include <string>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/HashCodeUtil.h>
#include <zserio/PreWriteAction.h>
#include <zserio/Types.h>

namespace tutorial
{

class Role
{
public:
    /**
     * The type this enum is based on.
     *
     * This is the C++ mapping of the original zserio type. It can be
     * wider than the original type. E.g. "enum bit:3" would have uint8_t
     * as its base type.
     */
    typedef uint8_t _base_type;

    enum e_Role
    {
        DEVELOPER = UINT8_C(0),
        TEAM_LEAD = UINT8_C(1),
        CTO = UINT8_C(2)
    };

    Role();
    Role(e_Role value);
    explicit Role(zserio::BitStreamReader& _in);

    operator e_Role() const;
    uint8_t getValue() const;

    size_t bitSizeOf(size_t _bitPosition = 0) const;
    size_t initializeOffsets(size_t _bitPosition = 0) const;

    bool operator==(const Role& other) const;
    bool operator==(e_Role other) const;
    int hashCode() const;

    void read(zserio::BitStreamReader& _in);
    void write(zserio::BitStreamWriter& _out,
            zserio::PreWriteAction _preWriteAction = zserio::ALL_PRE_WRITE_ACTIONS) const;

    const char* toString() const;

    static Role toEnum(uint8_t rawValue);

private:
    e_Role m_value;
};

} // namespace tutorial

#endif // TUTORIAL_ROLE_H
