import matplotlib
import matplotlib.pyplot as plt


if __name__ == "__main__":
    matplotlib.use('TkAgg')
    x = [5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    labels = ['Левенштейн', 'Дамерау-Левенштейн итер.', 'Дамерау-Левенштейн рек.', 'Дамерау-Левенштейн рек. кеш']
    plt.figure(figsize=(15.5, 9))
    plt.subplots_adjust(hspace=0.5)
    y_lev_iter = [0, 0, 0, 0, 0, 0, 0, 30.00, 32.04, 34.57, 62.36, 62.58, 94.90, 126.47, 156.01]
    y_dl_iter = [0, 0, 0, 0, 0, 12.57, 0, 32.21, 35.33, 41.03, 75.76, 94.60, 126.73, 172.12, 190.34]
    y_dl_rec = [0, 60.80, 319.94, 1807.34, 9831.58, 55262.60]
    y_dl_rec_cache = [0, 0, 0, 0, 0, 0, 0, 32.80, 64.04, 96.28, 128.47, 188.06, 282.39, 312.43, 360.07]

    plt.subplot(2, 2, 1)
    plt.plot(x[6:], y_lev_iter[6:], '--', label=labels[0])
    plt.plot(x[6:], y_dl_iter[6:], label=labels[1])
    plt.title("Нерекурсивные реализации")
    plt.xlabel("Количество символов", fontsize=14)
    plt.ylabel("Время, мкс", fontsize=14)
    plt.grid(True)
    plt.legend()

    plt.subplot(2, 2, 2)
    plt.plot(x[6:], y_dl_iter[6:], '--', label=labels[1])
    plt.plot(x[6:], y_dl_rec_cache[6:], label=labels[3])
    plt.title("Нерекурсивная реализация\nи рекурсивная с кешем")
    plt.xlabel("Количество символов", fontsize=14)
    plt.ylabel("Время, мкс", fontsize=14)
    plt.grid(True)
    plt.legend()

    plt.subplot(2, 2, 3)
    plt.plot(x[:6], y_lev_iter[:6], '-.', label=labels[0])
    plt.plot(x[:6], y_dl_iter[:6], '--', label=labels[1])
    plt.plot(x[:6], y_dl_rec[:6], '-*', label=labels[2])
    plt.plot(x[:6], y_dl_rec_cache[:6], label=labels[3])
    plt.title("Все реализации на длине до 10")
    plt.xlabel("Количество символов", fontsize=14)
    plt.ylabel("Время, мкс", fontsize=14)
    plt.grid(True)
    plt.legend()

    plt.subplot(2, 2, 4)
    plt.plot(x[6:], y_lev_iter[6:], '-.', label=labels[0])
    plt.plot(x[6:], y_dl_iter[6:], '--', label=labels[1])
    plt.plot(x[6:], y_dl_rec_cache[6:], label=labels[3])
    plt.title("Все реализации,\nкроме рекурсивной,\nна длине от 20")
    plt.xlabel("Количество символов", fontsize=14)
    plt.ylabel("Время, мкс", fontsize=14)
    plt.grid(True)
    plt.legend()

    plt.show()
