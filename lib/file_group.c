/* $Id$ */
#include "internal.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

UnshieldFileGroup* unshield_file_group_new(Header* header, uint32_t offset)/*{{{*/
{
  UnshieldFileGroup* self = NEW1(UnshieldFileGroup);
  uint8_t* p = unshield_header_get_buffer(header, offset);

  self->name = unshield_header_get_string(header, READ_UINT32(p)); p += 4;

  p += 0x48;

  self->first_file = READ_UINT32(p); p += 4;
  self->last_file  = READ_UINT32(p); p += 4;

  return self;
}/*}}}*/

void unshield_file_group_destroy(UnshieldFileGroup* self)/*{{{*/
{
  FREE(self);
}/*}}}*/

int unshield_file_group_count(Unshield* unshield)/*{{{*/
{
  Header* header = unshield->header_list;
  return header->file_group_count;
}/*}}}*/

UnshieldFileGroup* unshield_file_group_get(Unshield* unshield, int index)
{
  Header* header = unshield->header_list;

  if (index >= 0 && index < header->file_group_count)
    return header->file_groups[index];
  else
    return NULL;
}

UnshieldFileGroup* unshield_file_group_find(Unshield* unshield, const char* name)
{
  Header* header = unshield->header_list;
  int i;

  for (i = 0; i < header->file_group_count; i++)
  {
    if (STREQ(header->file_groups[i]->name, name))
      return header->file_groups[i];
  }

  return NULL;
}

const char* unshield_file_group_name(Unshield* unshield, int index)/*{{{*/
{
  Header* header = unshield->header_list;

  if (index >= 0 && index < header->file_group_count)
    return header->file_groups[index]->name;
  else
    return NULL;
}/*}}}*/
