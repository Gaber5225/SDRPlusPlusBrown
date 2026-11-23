#include <gui/style.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <config.h>
#include <utils/flog.h>
#include <filesystem>
#include "utils/wstr.h"
#include "brown/imgui-notify/tahoma.h"
#include "gui/brown/imgui-notify/imgui_notify.h"

namespace style {
    ImFont* notificationFont;
    ImFont* tinyFont;
    ImFont* baseFont;
    ImFont* bigFont;
    ImFont* mediumFont;
    ImFont* hugeFont;
    ImVector<ImWchar> baseRanges;
    ImVector<ImWchar> fullRanges;
    ImVector<ImWchar> bigRanges;
    ImVector<ImWchar> hugeRanges;

#ifndef __ANDROID__
    float uiScale = 1.0f;
#else
    float uiScale = 3.0f;
#endif

    bool loadFonts(std::string resDir) {
        ImFontAtlas* fonts = ImGui::GetIO().Fonts;
        if (!std::filesystem::is_directory(wstr::str2wstr(resDir))) {
            flog::error("Invalid resource directory: {0}", resDir);
            return false;
        }

        // Create base font range
        ImFontGlyphRangesBuilder baseBuilder;
        baseBuilder.AddRanges(fonts->GetGlyphRangesDefault());
        baseBuilder.AddRanges(fonts->GetGlyphRangesCyrillic());
        // Latin Extended-A, needed for Central European device and file names
        static const ImWchar latinExtA[] = { 0x0100, 0x017F, 0 };
        baseBuilder.AddRanges(latinExtA);
        // CJK support: common Simplified Chinese characters for medium/tiny
        // fonts (kept small so the atlas does not overflow).
        baseBuilder.AddRanges(fonts->GetGlyphRangesChineseSimplifiedCommon());
        // Add CJK characters used by the SDR++ Chinese UI but missing from
        // ImGui's SimplifiedCommon table, so they don't render as '?'.
        // Characters: 函嘶噪屏帧拟瀑糙纬聆谐钮阈频 (UTF-8, ASCII-escaped).
        baseBuilder.AddText("\xe5\x87\xbd\xe5\x98\xb6\xe5\x99\xaa\xe5\xb1\x8f\xe5\xb8\xa7\xe6\x8b\x9f\xe7\x80\x91\xe7\xb3\x99\xe7\xba\xac\xe8\x81\x86\xe8\xb0\x90\xe9\x92\xae\xe9\x98\x88\xe9\xa2\x91");
        baseBuilder.BuildRanges(&baseRanges);

        // Full CJK range for the main (base) font only. This covers all CJK
        // characters so no glyph shows as '?'. It is loaded on a single font
        // size (16px) to keep the atlas within the GPU texture limit.
        ImFontGlyphRangesBuilder fullBuilder;
        fullBuilder.AddRanges(fonts->GetGlyphRangesDefault());
        fullBuilder.AddRanges(fonts->GetGlyphRangesCyrillic());
        fullBuilder.AddRanges(latinExtA);
        fullBuilder.AddRanges(fonts->GetGlyphRangesChineseFull());
        fullBuilder.BuildRanges(&fullRanges);

        // Create big font range
        ImFontGlyphRangesBuilder bigBuilder;
//        const ImWchar bigRange[] = { '.', '9', '+', '-', 0 };
//        bigBuilder.AddRanges(bigRange);
        bigBuilder.AddRanges(fonts->GetGlyphRangesDefault());
        bigBuilder.BuildRanges(&bigRanges);

        // Create huge font range
        ImFontGlyphRangesBuilder hugeBuilder;
        const ImWchar hugeRange[] = { 'S', 'S', 'D', 'D', 'R', 'R', '+', '+', ' ', ' ', 0 };
        hugeBuilder.AddRanges(hugeRange);
        hugeBuilder.BuildRanges(&hugeRanges);
        
        // Add bigger fonts for frequency select and title
#ifdef __ANDROID__
        // Android uiScale is 3.0x (16px -> 48px), so loading the full CJK
        // range here overflows the font atlas texture (black boxes). Keep the
        // common Simplified range on Android; full CJK is used on desktop.
        baseFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/NotoSansSC-Regular.ttf")).c_str(), 16.0f * uiScale, NULL, baseRanges.Data);
#else
        baseFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/NotoSansSC-Regular.ttf")).c_str(), 16.0f * uiScale, NULL, fullRanges.Data);
#endif
        mediumFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/NotoSansSC-Regular.ttf")).c_str(), 25.0f * uiScale, NULL, baseRanges.Data);
        bigFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/NotoSansSC-Regular.ttf")).c_str(), 45.0f * uiScale, NULL, bigRanges.Data);
        hugeFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/NotoSansSC-Regular.ttf")).c_str(), 128.0f * uiScale, NULL, hugeRanges.Data);
        tinyFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/NotoSansSC-Regular.ttf")).c_str(), 12.0f * uiScale, NULL, baseRanges.Data);

        ImGuiIO* io = &ImGui::GetIO();
        // We must load a font before loading notify, because we cannot merge font-awesome with default font
        // FontDataOwnedByAtlas = false is required (also in ImGui::MergeIconsWithLatestFont())
        // because otherwise ImGui will call free() while freeing resources which will lead into a crash
        // since tahoma is defined as readonly and wasn't allocated with malloc()
        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        notificationFont = io->Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 20.f * uiScale, &font_cfg);

        // Initialize notify
        ImGui::MergeIconsWithLatestFont(16.f, false);



        return true;
    }

    void beginDisabled() {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        auto& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;
        ImVec4 btnCol = colors[ImGuiCol_Button];
        ImVec4 frameCol = colors[ImGuiCol_FrameBg];
        ImVec4 textCol = colors[ImGuiCol_Text];
        btnCol.w = 0.15f;
        frameCol.w = 0.30f;
        textCol.w = 0.65f;
        ImGui::PushStyleColor(ImGuiCol_Button, btnCol);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, frameCol);
        ImGui::PushStyleColor(ImGuiCol_Text, textCol);
    }

    void endDisabled() {
        ImGui::PopItemFlag();
        ImGui::PopStyleColor(3);
    }
}

namespace ImGui {
    void LeftLabel(const char* text) {
        float vpos = ImGui::GetCursorPosY();
        ImGui::SetCursorPosY(vpos + GImGui->Style.FramePadding.y);
        ImGui::TextUnformatted(text);
        ImGui::SameLine();
        ImGui::SetCursorPosY(vpos);
    }

    void FillWidth() {
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    }
}




