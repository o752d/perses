/*
 * Copyright (C) 2018-2020 University of Waterloo.
 *
 * This file is part of Perses.
 *
 * Perses is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3, or (at your option) any later version.
 *
 * Perses is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Perses; see the file LICENSE.  If not see <http://www.gnu.org/licenses/>.
 */

package org.perses.dot_graph;

import com.google.common.flogger.FluentLogger;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.TerminalNode;
import org.perses.antlr.ParseTreeWithParser;
import org.perses.grammar.ParserFacadeFactory;
import org.perses.program.SourceFile;
import org.perses.tree.spar.AbstractSparTreeNode;

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

public class TreeDotifier {
  private static final FluentLogger logger = FluentLogger.forEnclosingClass();
  private static final DotGraph.NodeLabelProvider<ParseTree>
      DEFAULT_ANTLR_PARSE_TREE_LABEL_PROVIDER =
          new DotGraph.NodeLabelProvider<ParseTree>() {
            @Override
            protected String computeNodeLabel(ParseTree node) {
              return node instanceof TerminalNode
                  ? node.getText()
                  : node.getClass().getSimpleName();
            }
          };
  private static final DotGraph.NodeLabelProvider<AbstractSparTreeNode>
      DEFAULT_RUNTIME_TREE_LABEL_PROVIDER =
          new DotGraph.NodeLabelProvider<AbstractSparTreeNode>() {
            @Override
            protected String computeNodeLabel(AbstractSparTreeNode node) {
              switch (node.getNodeType()) {
                case KLEENE_PLUS:
                  return "(+)";
                case KLEENE_STAR:
                  return "(*)";
                case OPTIONAL:
                  return "(?)";
                case TOKEN:
                  return node.asLexerRule().getToken().getText();
                case OTHER_RULE:
                  assert node.getAntlrRule().isPresent();
                  return node.getAntlrRule().get().getRuleName();
                default:
                  throw new AssertionError("Cannot reach here");
              }
            }
          };

  public static void main(String[] args) {
    dotifyAntlrParseTree(new File("test-programs/t6.c"), new File("temp.pdf"));
  }

  public static void dotifyAntlrParseTree(File sourceFile, File pdfFile) {
    try {
      ParserFacadeFactory factory = ParserFacadeFactory.builderWithBuiltinLanguages().build();
      final SourceFile source = new SourceFile(sourceFile, factory.computeLanguageKind(sourceFile));
      final ParseTreeWithParser root =
          factory.createParserFacade(source.getLanguageKind()).parseFile(sourceFile);
      convertTreeToDotGraph(root.getTree())
          .dotify(pdfFile, DEFAULT_ANTLR_PARSE_TREE_LABEL_PROVIDER);
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }

  public static void dotifyAntlrParseTree(
      ParseTree root, File pdfFile, DotGraph.NodeLabelProvider<ParseTree> labelProvider) {
    try {
      convertTreeToDotGraph(root).dotify(pdfFile, labelProvider);
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }

  public static void dotifyRuntimeMutableTree(AbstractSparTreeNode root, File pdfFile) {
    DotGraph<AbstractSparTreeNode> dotGraph = convertTreeToDotGraph(root);
    try {
      dotGraph.dotify(pdfFile, DEFAULT_RUNTIME_TREE_LABEL_PROVIDER);
      logger.atInfo().log("save dot graph to %s", pdfFile);
    } catch (IOException e) {
      throw new RuntimeException(e);
    }
  }

  public static void dotifyAntlrParseTree(ParseTree root, File pdfFile) {
    dotifyAntlrParseTree(root, pdfFile, DEFAULT_ANTLR_PARSE_TREE_LABEL_PROVIDER);
  }

  public static DotGraph<AbstractSparTreeNode> convertTreeToDotGraph(AbstractSparTreeNode root) {
    final DotGraph<AbstractSparTreeNode> graph = new DotGraph<>();
    final Queue<AbstractSparTreeNode> queue = new LinkedList<>();
    queue.add(root);
    while (queue.size() > 0) {
      final AbstractSparTreeNode node = queue.remove();
      final int childCount = node.getChildCount();
      for (int i = 0; i < childCount; ++i) {
        final AbstractSparTreeNode child = node.getChild(i);
        graph.addEdge(node, child);
        queue.add(child);
      }
    }
    return graph;
  }

  public static DotGraph<ParseTree> convertTreeToDotGraph(ParseTree root) {
    final DotGraph<ParseTree> graph = new DotGraph<>();
    final Queue<ParseTree> queue = new LinkedList<>();
    queue.add(root);
    while (queue.size() > 0) {
      final ParseTree node = queue.remove();
      final int childCount = node.getChildCount();
      for (int i = 0; i < childCount; ++i) {
        final ParseTree child = node.getChild(i);
        graph.addEdge(node, child);
        queue.add(child);
      }
    }
    return graph;
  }
}
