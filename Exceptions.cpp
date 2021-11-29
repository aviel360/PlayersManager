//
// Created by Sofia Blyufer on 28/11/2021.
//

#include "Exceptions.h"
/**
 *
 * @return
 */
const char * Exception::what () const noexcept
{
    return "A game related error has occurred: Exception";
}
/**
 *
 * @return
 */
const char * ValueExists::what () const noexcept
{
    return "A game related error has occurred: Value already exists";
}
/**
 *
 * @return
 */
const char * ValueNotExists::what () const noexcept
{
    return "A game related error has occurred: Value Doesn't exists";
}

const char * InvalidInput::what () const noexcept
{
    return "A game related error has occurred: Invalid Input";
}