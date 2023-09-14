#include "mainwindow.h"
#include <QApplication>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <iostream>
#include <vector>

#include <Eigen/Eigen>
#include <Eigen/Dense>

//#include <pcl/io/pcd_io.h>
//#include <pcl/point_types.h>
//#include <pcl/visualization/pcl_visualizer.h>


class EnvTest {
public:
    void testVTK() {
        qDebug() << "testVTK" << Qt::endl;

        vtkNew<vtkNamedColors> colors;

        // Set the background color.
        std::array<unsigned char, 4> bkg{26, 51, 102, 255};
        colors->SetColor("BkgColor", bkg.data());

        // This creates a polygonal cylinder model with eight circumferential facets
        // (i.e, in practice an octagonal prism).
        vtkNew<vtkCylinderSource> cylinder;
        cylinder->SetResolution(8);

        // The mapper is responsible for pushing the geometry into the graphics
        // library. It may also do color mapping, if scalars or other attributes are
        // defined.
        vtkNew<vtkPolyDataMapper> cylinderMapper;
        cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

        // The actor is a grouping mechanism: besides the geometry (mapper), it
        // also has a property, transformation matrix, and/or texture map.
        // Here we set its color and rotate it around the X and Y axes.
        vtkNew<vtkActor> cylinderActor;
        cylinderActor->SetMapper(cylinderMapper);
        cylinderActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());
        cylinderActor->RotateX(30.0);
        cylinderActor->RotateY(-45.0);

        // The renderer generates the image
        // which is then displayed on the render window.
        // It can be thought of as a scene to which the actor is added
        vtkNew<vtkRenderer> renderer;
        renderer->AddActor(cylinderActor);
        renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
        // Zoom in a little by accessing the camera and invoking its "Zoom" method.
        renderer->ResetCamera();
        renderer->GetActiveCamera()->Zoom(1.5);

        // The render window is the actual GUI window
        // that appears on the computer screen
        vtkNew<vtkRenderWindow> renderWindow;
        renderWindow->SetSize(800, 800);
        renderWindow->AddRenderer(renderer);
        renderWindow->SetWindowName("Cylinder");

        // The render window interactor captures mouse events
        // and will perform appropriate camera or actor manipulation
        // depending on the nature of the events.
        vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
        renderWindowInteractor->SetRenderWindow(renderWindow);

        // This starts the event loop and as a side effect causes an initial render.
        renderWindow->Render();
        renderWindowInteractor->Start();

    }

    void testITK() {
        qDebug() << "testITK" << Qt::endl;

        using ImageType = itk::Image<unsigned short, 3>;
        ImageType::Pointer image = ImageType::New();
    }

    void testEigen() {
        qDebug() << "testEigen";
        // 创建3x3的矩阵
        Eigen::MatrixXd A(3, 3);
        A << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;

        // 创建3维向量
        Eigen::VectorXd b(3);
        b << 10, 20, 30;

        // 求解线性方程 Ax = b
        Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

        // 输出解向量
        std::cout << "Solution x:\n" << x << std::endl;
        std::cout << std::flush;

        // 矩阵乘法
        Eigen::MatrixXd C = A * A.transpose();

        // 输出结果矩阵
        std::cout << "Result matrix C:\n" << C << std::endl;
        std::cout << std::flush;
    }

//    void testPCL() {
//        // 创建点云对象
//        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

//        // 从PCD文件读取点云数据
//        if (pcl::io::loadPCDFile<pcl::PointXYZ>("sample_cloud.pcd", *cloud) == -1)
//        {
//            PCL_ERROR("Couldn't read file sample_cloud.pcd\n");
//            return -1;
//        }

//        // 创建PCL可视化器
//        pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Cloud Viewer"));

//        // 设置点云颜色为绿色
//        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 0, 255, 0);
//        viewer->addPointCloud<pcl::PointXYZ>(cloud, single_color, "sample cloud");

//        // 设置背景颜色
//        viewer->setBackgroundColor(0, 0, 0);

//        // 添加坐标系
//        viewer->addCoordinateSystem(1.0);

//        // 启动可视化循环
//        while (!viewer->wasStopped())
//        {
//            viewer->spinOnce(100);
//        }

//    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    MainWindow mainWin;
//    mainWin.resize(800, 600);
//    mainWin.show();

    EnvTest t;
    t.testEigen();
//    t.testPCL();
    t.testITK();
    t.testVTK();

    return app.exec();
}
