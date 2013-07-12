#ifndef ASLAM_BACKEND_EUCLIDEAN_EXPRESSION_NODE_HPP
#define ASLAM_BACKEND_EUCLIDEAN_EXPRESSION_NODE_HPP

#include <aslam/backend/JacobianContainer.hpp>
#include "RotationExpressionNode.hpp"
#include "MatrixExpressionNode.hpp"
#include <boost/shared_ptr.hpp>
#include <Eigen/Core>


namespace aslam {
  namespace backend {
    template <int D> class VectorExpression;
    template <int D> class VectorExpressionNode;

    /**
     * \class EuclideanExpressionNode
     * \brief The superclass of all classes representing euclidean points.
     */
    class EuclideanExpressionNode
    {
    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW

      EuclideanExpressionNode();
      virtual ~EuclideanExpressionNode();

      /// \brief Evaluate the euclidean matrix.
      Eigen::Vector3d toEuclidean();
      
      /// \brief Evaluate the Jacobians
      void evaluateJacobians(JacobianContainer & outJacobians) const;   
    
      /// \brief Evaluate the Jacobians and apply the chain rule.
      void evaluateJacobians(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
      void getDesignVariables(DesignVariable::set_t & designVariables) const;
    protected:        
      // These functions must be implemented by child classes.
      virtual Eigen::Vector3d toEuclideanImplementation() = 0;
      virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const = 0;
      virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const = 0;
      virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const = 0;
    };


    /**
     * \class EuclideanExpressionNodeMultiply
     *
     * \brief A class representing the multiplication of two euclidean matrices.
     * 
     */
    class EuclideanExpressionNodeMultiply : public EuclideanExpressionNode
    {
    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW

      EuclideanExpressionNodeMultiply(boost::shared_ptr<RotationExpressionNode> lhs, 
				     boost::shared_ptr<EuclideanExpressionNode> rhs);
      virtual ~EuclideanExpressionNodeMultiply();

    private:
      virtual Eigen::Vector3d toEuclideanImplementation();
      virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
      virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
      virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

      boost::shared_ptr<RotationExpressionNode> _lhs;
      Eigen::Matrix3d _C_lhs;
      boost::shared_ptr<EuclideanExpressionNode> _rhs;
      Eigen::Vector3d _p_rhs;


    };

    // ## New Class for Multiplication with a MatrixExpression
    /**
      * \class EuclideanExpressionNodeMatrixMultiply
      *
      * \brief A class representing the multiplication of a Matrix with a euclidean Vector.
      *
      */
     class EuclideanExpressionNodeMatrixMultiply : public EuclideanExpressionNode
     {
     public:
       EIGEN_MAKE_ALIGNED_OPERATOR_NEW

       EuclideanExpressionNodeMatrixMultiply(boost::shared_ptr<MatrixExpressionNode> lhs, boost::shared_ptr<EuclideanExpressionNode> rhs);
       virtual ~EuclideanExpressionNodeMatrixMultiply();

     private:
       virtual Eigen::Vector3d toEuclideanImplementation();
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
       virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

       boost::shared_ptr<MatrixExpressionNode> _lhs;
       Eigen::Matrix3d _A_lhs;
       boost::shared_ptr<EuclideanExpressionNode> _rhs;
       Eigen::Vector3d _p_rhs;

     };



    /**
      * \class EuclideanExpressionNodeCrossEuclidean
      *
      * \brief A class representing the cross product of two euclidean expressions.
      *
      */
     class EuclideanExpressionNodeCrossEuclidean : public EuclideanExpressionNode
     {
     public:
       EIGEN_MAKE_ALIGNED_OPERATOR_NEW

       EuclideanExpressionNodeCrossEuclidean(boost::shared_ptr<EuclideanExpressionNode> lhs,
           boost::shared_ptr<EuclideanExpressionNode> rhs);
       virtual ~EuclideanExpressionNodeCrossEuclidean();

     private:
       virtual Eigen::Vector3d toEuclideanImplementation();
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
       virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

       boost::shared_ptr<EuclideanExpressionNode> _lhs;
       boost::shared_ptr<EuclideanExpressionNode> _rhs;
     };


     /**
       * \class EuclideanExpressionNodeAddEuclidean
       *
       * \brief A class representing the addition of two euclidean expressions.
       *
       */
      class EuclideanExpressionNodeAddEuclidean : public EuclideanExpressionNode
      {
      public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        EuclideanExpressionNodeAddEuclidean(boost::shared_ptr<EuclideanExpressionNode> lhs,
            boost::shared_ptr<EuclideanExpressionNode> rhs);
        virtual ~EuclideanExpressionNodeAddEuclidean();

      private:
        virtual Eigen::Vector3d toEuclideanImplementation();
        virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
        virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
        virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

        boost::shared_ptr<EuclideanExpressionNode> _lhs;
        boost::shared_ptr<EuclideanExpressionNode> _rhs;
      };


      /**
      * \class EuclideanExpressionNodeSubtractEuclidean
      *
      * \brief A class representing the subtraction of two Euclidean expressions.
      *
      */
     class EuclideanExpressionNodeSubtractEuclidean : public EuclideanExpressionNode
     {
     public:
       EIGEN_MAKE_ALIGNED_OPERATOR_NEW

       EuclideanExpressionNodeSubtractEuclidean(boost::shared_ptr<EuclideanExpressionNode> lhs,
           boost::shared_ptr<EuclideanExpressionNode> rhs);
       virtual ~EuclideanExpressionNodeSubtractEuclidean();

     private:
       virtual Eigen::Vector3d toEuclideanImplementation();
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
       virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

       boost::shared_ptr<EuclideanExpressionNode> _lhs;
       boost::shared_ptr<EuclideanExpressionNode> _rhs;
     };


    /**
      * \class EuclideanExpressionNodeSubtractVector
      *
      * \brief A class representing the subtraction of a vector from an Euclidean expression.
      *
      */
     class EuclideanExpressionNodeSubtractVector : public EuclideanExpressionNode
     {
     public:
       EIGEN_MAKE_ALIGNED_OPERATOR_NEW

       EuclideanExpressionNodeSubtractVector(boost::shared_ptr<EuclideanExpressionNode> lhs,
              Eigen::Vector3d rhs);
       virtual ~EuclideanExpressionNodeSubtractVector();

     private:
       virtual Eigen::Vector3d toEuclideanImplementation();
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
       virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
       virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

       boost::shared_ptr<EuclideanExpressionNode> _lhs;
       Eigen::Vector3d _rhs;
     };


     /**
       * \class EuclideanExpressionNodeSubtractVector
       *
       * \brief A class representing the negated Euclidean expression.
       *
       */
      class EuclideanExpressionNodeNegated : public EuclideanExpressionNode
      {
      public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        EuclideanExpressionNodeNegated(boost::shared_ptr<EuclideanExpressionNode> operand);
        virtual ~EuclideanExpressionNodeNegated();

      private:
        virtual Eigen::Vector3d toEuclideanImplementation();
        virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
        virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
        virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

        boost::shared_ptr<EuclideanExpressionNode> _operand;
      };

     /**
       * \class VectorExpression2EuclideanExpressionAdapter
       *
       * \brief A class representing an adapted VectorExpression<3>.
       *
       */
      class VectorExpression2EuclideanExpressionAdapter : public EuclideanExpressionNode
      {
      public:
        VectorExpression2EuclideanExpressionAdapter(boost::shared_ptr<VectorExpressionNode<3> > vectorExpressionNode);
        virtual ~VectorExpression2EuclideanExpressionAdapter();

      private:
        virtual Eigen::Vector3d toEuclideanImplementation();
        virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians) const;
        virtual void evaluateJacobiansImplementation(JacobianContainer & outJacobians, const Eigen::MatrixXd & applyChainRule) const;
        virtual void getDesignVariablesImplementation(DesignVariable::set_t & designVariables) const;

        boost::shared_ptr<VectorExpressionNode<3> > _vectorExpressionNode;
      };

  } // namespace backend
} // namespace aslam

#endif /* ASLAM_BACKEND_EUCLIDEAN_EXPRESSION_NODE_HPP */
