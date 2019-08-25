//
// Created by MrJaqbq on 2016-02-14.
//

#include "Platform/Logger.h"
#include "Platform/Window.h"
#include "Platform/Platform.h"
#include "Platform/Subsystem/ISubsystem.h"

#include "RTTI/ClassInfo.h"

YAGE_DEFINE_CLASS_RTTI(Core::Window);

namespace Core
{
    Window::Window(Memory::IMemoryBlock& memory, const char* title, unsigned width, unsigned height)
        : _memory(&memory), Title {title}, Width {width}, Height {height},
          hWindow {nullptr}, IsCloseRequested(false)
    {
        Create();
    }

    Window::~Window()
    {
        Destroy();
    }

    auto Window::GetNative() const -> yage::platform::WindowHandle
    {
        return hWindow;
    }

    void Window::Create()
    {
        if (IsAlive())
            return;

        yage::platform::SWindowParams params;
        params.height = Height;
        params.width = Width;
        params.name = Title;

        auto& sys = yage::platform::getSubsystem();

        hWindow = sys.createWindow(params);

        if (hWindow == nullptr)
        {
            Core::Logger::error("Subsystem : Failed to create window!");
            return;
        }
    }

    auto Window::Show() const noexcept -> void
    {
        if (!IsAlive())
            return;

        yage::platform::getSubsystem().showWindow(hWindow);
    }

    void Window::OnResize(std::int32_t width, std::int32_t height)
    {
        if (width == Width && height == Height)
            return;

        Width  = width;
        Height = height;

    /*
        // Renderer should subscribe for this event
        DefaultViewport->setRect(Gfx::Rectangle<int32_t>(0, 0, Width, Height));
        OpenGL::resizeWindow(*this);
    */
    }

    auto Window::Resize(std::int32_t width, std::int32_t height) -> void
    {
        yage::platform::getSubsystem().resizeWindow(hWindow, width, height);
    }

    void Window::Close()
    {
        IsCloseRequested = true;
    }

    auto Window::Destroy() -> void
    {
        if (!IsAlive())
            return;

        yage::platform::getSubsystem().destroyWindow(hWindow);

        hWindow = nullptr;
    }

    auto Window::IsAlive() const noexcept -> bool
    {
        return hWindow != nullptr;
    }

    auto Window::ShouldClose() const noexcept -> bool
    {
        return !IsAlive() || IsCloseRequested;
    }
}