#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <memory>

//=========================================================
//                Base Class: Project
//=========================================================
class Project {
protected:
    QString name;
    double cost;
    double revenue;
    int competitors;
    int difficulty;

public:
    Project(QString n, double c, double r, int comp, int diff)
        : name(n), cost(c), revenue(r),
        competitors(comp), difficulty(diff) {}

    virtual double risk() const = 0;

    int evaluate() const {
        if (cost <= 0) return 0;
        double netProfit = revenue - cost;
        double profitMargin = (netProfit / cost) * 100.0;
        double score = 50 + (profitMargin / 2);
        if (competitors > 10) score -= 20;
        score -= difficulty * 5;
        score -= risk();
        if (score > 100) return 100;
        if (score < 0) return 0;
        return static_cast<int>(score);
    }

    virtual QString getDetailedAnalysis() const {
        QString analysis;
        double monthlyRevenue = revenue / 3.0;

        analysis += "<b style='color:#87CEEB;'>Quarterly Analysis (تحليل الـ 3 أشهر الأولى):</b><br>";
        analysis += "<hr style='border:1px solid #87CEEB;'>";
        analysis += "• Est. Monthly Income (الدخل الشهري المتوقع): <b style='color:#ffffff;'>$" + QString::number(monthlyRevenue, 'f', 2) + "</b><br>";

        if (revenue < cost) {
            analysis += "<span style='color:#ffb3b3;'>• Warning: Low Return (تنبيه: عوائد منخفضة).</span><br>";
            analysis += "• AI Tip: Optimize Startup Cost (نصيحة: حسن تكاليف التأسيس).<br>";
        } else {
            analysis += "<span style='color:#a2ffb3;'>• Status: Profitable (الحالة: مشروع رابح).</span><br>";
        }
        return analysis;
    }

    virtual ~Project() {}
    double getCost() const { return cost; }
    double getRevenue() const { return revenue; }
};

class ServiceProject : public Project {
    int staff;
public:
    ServiceProject(QString n, double c, double r, int comp, int diff, int s)
        : Project(n, c, r, comp, diff), staff(s) {}

    double risk() const override { return (staff < 2) ? 15 : 0; }

    QString getDetailedAnalysis() const override {
        QString res = Project::getDetailedAnalysis();
        if (staff > 10)
            res += "• <b>Staff Warning (تحذير العمالة):</b> Check workforce efficiency (راجع كفاءة العمالة).<br>";
        return res;
    }
};

class ProductProject : public Project {
    double storage;
public:
    ProductProject(QString n, double c, double r, int comp, int diff, double st)
        : Project(n, c, r, comp, diff), storage(st) {}
    double risk() const override { return (storage > revenue * 0.1) ? 20 : 5; }
};

//=========================================================
//          Analytical AI (English + Arabic)
//=========================================================
QString generateAdvancedAI(int score, Project* p) {
    QString advice = "<h2 style='color:#87CEEB;'>AI Deep Report (تقرير الـ AI العميق) 🤖</h2>";

    if (score >= 70) {
        advice += "<b>Status: Excellent (الحالة: ممتاز)</b><br>";
        advice += "Model shows high stability (النموذج يظهر استقرار عالي).";
    } else {
        advice += "<b>Status: Optimization Needed (الحالة: يحتاج تحسين)</b><br>";
        advice += "1. Review Budget Allocation (راجع توزيع الميزانية).<br>";
        advice += "2. Increase Revenue Targets (ارفع أهداف الأرباح).";
    }
    return advice;
}

//=========================================================
//                    Main Function
//=========================================================
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // SKY BLUE & DARK SLATE THEME
    app.setStyleSheet(
        "QWidget { background-color: #1a1a2e; color: #ffffff; font-family: 'Segoe UI', sans-serif; font-size: 15px; }"
        "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox { "
        "   background-color: #16213e; border: 2px solid #87CEEB; border-radius: 6px; "
        "   padding: 8px; color: #ffffff; }"
        "QPushButton { "
        "   background-color: #87CEEB; color: #1a1a2e; font-weight: bold; "
        "   border-radius: 10px; padding: 15px; border: none; text-transform: uppercase; }"
        "QPushButton:hover { background-color: #00d2ff; color: #ffffff; }"
        "QLabel#ResultBox { "
        "   background-color: #0f3460; border: 2px solid #87CEEB; border-radius: 12px; "
        "   padding: 20px; color: #ffffff; font-size: 16px; }"
        );

    QWidget window;
    window.setWindowTitle("STARTUP ANALYZER AI - (SKY BLUE EDITION)");
    window.resize(700, 900);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->setContentsMargins(30, 30, 30, 30);
    layout->setSpacing(20);

    QFormLayout *form = new QFormLayout;
    form->setSpacing(15);
    form->setLabelAlignment(Qt::AlignLeft);

    // INPUTS
    QLineEdit *name = new QLineEdit;
    QDoubleSpinBox *cost = new QDoubleSpinBox; cost->setMaximum(1e9); cost->setPrefix("$ ");
    QDoubleSpinBox *revenue = new QDoubleSpinBox; revenue->setMaximum(1e9); revenue->setPrefix("$ ");
    QSpinBox *competitors = new QSpinBox;
    QSpinBox *difficulty = new QSpinBox; difficulty->setRange(1, 5);
    QComboBox *type = new QComboBox; type->addItems({"Service Based (خدمي)", "Product Based (إنتاجي)"});
    QSpinBox *staff = new QSpinBox;
    QDoubleSpinBox *storage = new QDoubleSpinBox; storage->setMaximum(1e9); storage->setPrefix("$ "); storage->hide();

    // LABELS (English + Arabic)
    form->addRow("Project Name (اسم المشروع):", name);
    form->addRow("Startup Cost (تكلفة التأسيس):", cost);
    form->addRow("3rd Month Revenue (أرباح 3 أشهر):", revenue);
    form->addRow("Competitors (عدد المنافسين):", competitors);
    form->addRow("Difficulty (الصعوبة 1-5):", difficulty);
    form->addRow("Business Type (نوع النشاط):", type);
    form->addRow("Staff Count (عدد الموظفين):", staff);
    form->addRow("Storage Cost (تكلفة التخزين):", storage);

    QLabel *result = new QLabel("Analysis will appear here (التحليل سيظهر هنا)...");
    result->setObjectName("ResultBox");
    result->setWordWrap(true);

    QPushButton *btn = new QPushButton("Evaluate Project (إجراء التقييم)");
    QPushButton *aiBtn = new QPushButton("Deep AI Analysis (تحليل AI عميق) 🤖");

    layout->addLayout(form);
    layout->addWidget(btn);
    layout->addWidget(aiBtn);
    layout->addWidget(result);

    QObject::connect(type, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        staff->setVisible(index == 0);
        storage->setVisible(index == 1);
    });

    static std::unique_ptr<Project> currentProject;

    QObject::connect(btn, &QPushButton::clicked, [&]() {
        if (name->text().isEmpty()) {
            result->setText("<b style='color:#87CEEB;'>Error: Enter Name (خطأ: أدخل الاسم)</b>");
            return;
        }
        if (type->currentIndex() == 0)
            currentProject = std::make_unique<ServiceProject>(name->text(), cost->value(), revenue->value(), competitors->value(), difficulty->value(), staff->value());
        else
            currentProject = std::make_unique<ProductProject>(name->text(), cost->value(), revenue->value(), competitors->value(), difficulty->value(), storage->value());

        int score = currentProject->evaluate();
        result->setText("<b style='color:#87CEEB; font-size:20px;'>Score (النتيجة): " + QString::number(score) + "/100</b><br><br>" + currentProject->getDetailedAnalysis());
    });

    QObject::connect(aiBtn, &QPushButton::clicked, [&]() {
        if (!currentProject) {
            QMessageBox::critical(&window, "Error (خطأ)", "Evaluate first (قيم أولاً)");
            return;
        }
        QMessageBox msgBox;
        msgBox.setWindowTitle("AI Deep Report");
        msgBox.setText(generateAdvancedAI(currentProject->evaluate(), currentProject.get()));
        msgBox.setStyleSheet("QLabel{min-width: 400px; color: white;} QPushButton{ background-color: #87CEEB; color: #1a1a2e; font-weight: bold; }");
        msgBox.exec();
    });

    window.show();
    return app.exec();
}