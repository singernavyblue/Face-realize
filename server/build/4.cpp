/*************************************************************************
	> File Name: 4.cpp
	> Author: csgec
	> Mail: 12345678@qq.com 
	> Created Time: 2023年07月13日 星期四 11时14分17秒
 ************************************************************************/

#include <gtkmm.h>
#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>
#include <ifaddrs.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow() : button("开始运行"), label_ip("IP 地址: "), label_port("端口号: ") {
        set_title("服务器");
        set_border_width(10);
        set_default_size(400, 200);  // 设置默认窗口大小

        // 创建 CSS 提供者
        auto css_provider = Gtk::CssProvider::create();
        css_provider->load_from_path("background.css"); // 加载CSS文件

        // 设置窗口样式上下文
        auto style_context = get_style_context();
        style_context->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));
        add(vbox);

        // 创建 IP 地址输入框
        hbox_ip.pack_start(label_ip, Gtk::PACK_EXPAND_PADDING);
        hbox_ip.pack_start(entry_ip, Gtk::PACK_EXPAND_PADDING);
        vbox.pack_start(hbox_ip, Gtk::PACK_EXPAND_PADDING);

        // 创建 端口号输入框
        hbox_port.pack_start(label_port, Gtk::PACK_EXPAND_PADDING);
        hbox_port.pack_start(entry_port, Gtk::PACK_EXPAND_PADDING);
        vbox.pack_start(hbox_port, Gtk::PACK_EXPAND_PADDING);

        vbox.pack_start(button, Gtk::PACK_EXPAND_PADDING);
        show_all_children();
    }

    virtual ~MainWindow() {}

protected:
    Gtk::Button button;
    Gtk::VBox vbox;
    Gtk::HBox hbox_ip, hbox_port;
    Gtk::Label label_ip, label_port;
    Gtk::Entry entry_ip, entry_port;

    void on_button_clicked() {
        std::string ip = entry_ip.get_text();
        // Get the local IP address
        std::string local_ip;
        struct ifaddrs *ifaddr, *ifa;
        if (getifaddrs(&ifaddr) == -1) {
            perror("getifaddrs");
            exit(EXIT_FAILURE);
        }
        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_INET) {
                continue;
            }
            struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
            char *ip_addr = inet_ntoa(addr->sin_addr);
            if (std::string(ip_addr) != "127.0.0.1") {
                local_ip = ip_addr;
                break;
            }
        }
        freeifaddrs(ifaddr);
        // Validate the IP address. Here, we are checking if the IP address is equal to the local IP address.
        if (ip.empty() || ip != local_ip) {
            Gtk::MessageDialog dialog(*this, "错误", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("请输入正确IP地址");
            dialog.run();
            return;
        }
        // If the IP address is valid, execute the client and server programs.
        
        std::system("./S1 &");
    }
};

int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MainWindow window;
    return app->run(window);
}
