//===- ScopStmt.h -----------------------------------------------*- C++ -*-===//
//
// This file declares the class ScopStmt.
//
//===----------------------------------------------------------------------===//

#ifndef POLYMER_SUPPORT_SCOPSTMT_H
#define POLYMER_SUPPORT_SCOPSTMT_H

#include <memory>

#include "llvm/ADT/SmallVector.h"

namespace mlir {
class Operation;
class FlatAffineConstraints;
class AffineValueMap;
class FuncOp;
class CallOp;
class Value;
} // namespace mlir

namespace polymer {
class ScopStmtImpl;

/// Class that stores all the essential information for a Scop statement,
/// including the MLIR operations and Scop relations (represented by
/// FlatAffineConstraints), and handles the processing of them. A ScopStmt can
/// be constructed from a pair of caller and callee, the callee contains the
/// operations inside a ScopStmt, and the caller indicates where this statement
/// is called and the bindings of arguments.
class ScopStmt {
public:
  ScopStmt(mlir::Operation *caller, mlir::Operation *callee);
  ~ScopStmt();

  ScopStmt(ScopStmt &&);
  ScopStmt(const ScopStmt &) = delete;
  ScopStmt &operator=(ScopStmt &&);
  ScopStmt &operator=(const ScopStmt &&) = delete;

  /// Get the callee of this scop stmt.
  mlir::FuncOp getCallee() const;
  /// Get the caller of this scop stmt.
  mlir::CallOp getCaller() const;

  /// Get the pointer to the domain.
  mlir::FlatAffineConstraints *getDomain() const;
  /// Get a copy of the enclosing operations.
  void getEnclosingOps(llvm::SmallVectorImpl<mlir::Operation *> &ops,
                       bool forOnly = false) const;
  /// Get the access AffineValueMap of an op in the callee and the memref in the
  /// caller scope that this op is using.
  void getAccessMapAndMemRef(mlir::Operation *op, mlir::AffineValueMap *vMap,
                             mlir::Value *memref) const;

private:
  std::unique_ptr<ScopStmtImpl> impl;
};
} // namespace polymer

#endif
