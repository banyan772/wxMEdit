///////////////////////////////////////////////////////////////////////////////
// vim:         ts=4 sw=4 expandtab
// Name:        wxm_utils.h
// Description: Utility Functions
// Author:      madedit@gmail.com  (creator)
//              wxmedit@gmail.com  (current maintainer)
// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////

#ifndef _WXM_UTILS_H_
#define _WXM_UTILS_H_

#include "xm/wxm_choice_map.hpp"
#include "xm/wxm_def.h"

#include <wx/defs.h>
#include <wx/string.h>
#include <boost/shared_ptr.hpp>
#include <map>
#include <vector>

struct HtmlColor
{
    const wxChar *name;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
extern HtmlColor HtmlColorTable[];
extern const int HtmlColorTableCount;

extern std::map<wxString, wxString> g_color_l10n_map;

extern wxString GetExecutablePath();

class wxWindow;
class MadEdit;

namespace wxm
{

void SetL10nHtmlColors();

void OpenURL(const wxString& url);

void SetDefaultMonoFont(wxWindow* win);

wxString FilePathNormalCase(const wxString& path);
bool FilePathEqual(const wxString& path1, const wxString& path2);
unsigned long FilePathHash(const wxString& path);

struct FileList
{
    FileList(const wxString& files = wxString())
    {
        Init(files);
    }
    FileList(const wchar_t* files)
    {
        Init(wxString(files));
    }

    void Append(const wxString& file, const LineNumberList& bmklns=LineNumberList());

    const wxString& String()
    {
        return m_files;
    }

    struct FileDesc
    {
        wxString file;
        LineNumberList bmklinenums;

        FileDesc() {}
        FileDesc(const wxString& f, const LineNumberList& lns) : file(f), bmklinenums(lns) {}
    };

    typedef std::vector<FileDesc> FDescList;

    const FDescList& List()
    {
        return m_filevec;
    }

private:
    void Init(const wxString& files);

    wxString m_files;
    FDescList m_filevec;
};

struct HexAreaClipboardCopier
{
    virtual void Copy(MadEdit* inst) = 0;
    virtual ~HexAreaClipboardCopier() {}
};

typedef boost::shared_ptr<HexAreaClipboardCopier> SharedCopierPtr;
struct HexAreaClipboardCopyProxy: public ChoiceMap<HexAreaClipboardCopyProxy, SharedCopierPtr>
{
    void SelectCopierByConfig(const wxString& cfg)
    {
        m_selected_idx = ConfigToIndex(cfg);
    }

    wxString GetSelectedCopierTitle()
    {
        return IndexToTitle(m_selected_idx);
    }

    HexAreaClipboardCopier& GetSelectedCopier()
    {
        return *IndexToVal(m_selected_idx);
    }

private:
    friend class ChoiceMap<HexAreaClipboardCopyProxy, SharedCopierPtr>;
    HexAreaClipboardCopyProxy(): m_selected_idx(HACCI_RAWBYTES) {}

    virtual void DoInit();

    enum HexAreaClipboardCopierIndex
    {
        HACCI_RAWBYTES,
        HACCI_REGULARTEXT,
        HACCI_HEXSTRING,
        HACCI_HEXSTRINGWITHSPACE,
    };

    int m_selected_idx;
};

} //namespace wxm

#endif
